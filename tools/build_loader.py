"""Build build/loader/nfsu2decomp.asi: the runtime loader plus every hookable recompiled function.

  python tools/check.py               (first: compiles everything and records which functions match)
  python tools/build_loader.py        build and verify the .asi
  python tools/build_loader.py --install   also copy it to <game>/scripts/

How references to the original game are resolved, in order:
  1. derived from the original bytes: in a byte-matched function every relocated field sits at the
     same offset as in SPEED2.EXE, so the original bytes tell us the real target of each symbol
  2. an address in the name: sub_4604E0, g_7ED468, fn_72A672, ...
  3. yugecin's name for it (config/symbols.csv), after demangling
  4. config/externs.csv (mangled name, address)
  anything else is left to the C runtime library.
Calls go through small jmp stubs (the linker cannot call an absolute address); data references
become absolute symbols. Objects that construct classes have their vtable references pointed at the
game's real vtables, so objects we create are indistinguishable from the game's own.
After linking, every hooked function is compared with the original: identical bytes, and every
relocated field must reach the same target (or a copy with identical contents).
"""
import csv, json, os, re, shutil, struct, subprocess, sys, zlib

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

OUT = os.path.join(common.BUILD, "loader")
DIR32, REL32 = 0x06, 0x14
ADDR_IN_NAME = re.compile(r"(?:sub|fn|g|dword|byte|word|flt|dbl|off|unk|stru|vtable)_([0-9A-Fa-f]{6})(?![0-9A-Fa-f])")


def run(*cmd, cwd=OUT):
    p = subprocess.run(cmd, capture_output=True, text=True, env=common.cc_env(), cwd=cwd)
    return p.returncode, (p.stdout + p.stderr).strip()


def u32(b, o=0):
    return struct.unpack_from("<I", b, o)[0]


def s32(b, o=0):
    return struct.unpack_from("<i", b, o)[0]


# ---------------------------------------------------------------- choose objects and hooks

def select(results, include_equivalent):
    by_obj = {}
    for r in results:
        if r.get("obj"):
            by_obj.setdefault(r["obj"], []).append(r)
    chosen, excluded = {}, []
    for obj, rs in sorted(by_obj.items()):
        d = open(obj, "rb").read()
        secs, syms = common.parse_coff(d)
        reason = None
        for s in syms:
            if s["section"] > 0 and s["class"] == 2 and s["type"] != 0x20:
                sec = secs[s["section"] - 1]
                comdat = sec["chars"] & 0x1000
                if not comdat and not s["name"].startswith(("??_C@", "__real@", "$")):
                    reason = "defines global data %s (it must stay the game's)" % s["name"]
            if s["section"] == 0 and s["class"] == 2 and s["value"] > 0:
                reason = "defines common data %s" % s["name"]
        for r in rs:
            ok_status = r["status"] == "match" or (include_equivalent and r["status"] == "equivalent")
            size = common.functions().get(r["addr"], {}).get("size", 0)
            why = reason or (None if ok_status else "status is %s" % r["status"])
            why = why or ("NOHOOK" if r.get("nohook") else None) or ("original is under 5 bytes" if size < 5 else None)
            if why:
                excluded.append((r["addr"], r["file"], why))
            else:
                chosen.setdefault(obj, []).append(r)
    return chosen, excluded


# ---------------------------------------------------------------- derive addresses from matched code

def derive(chosen):
    derived, conflicts = {}, []
    for obj, rs in chosen.items():
        funcs = common.coff_functions(obj)
        # symbols the object defines itself (jump table labels, statics, EH data) stay ours; only
        # vtables are swapped for the game's
        _, syms = common.parse_coff(open(obj, "rb").read())
        local = {s["name"] for s in syms if s["section"] > 0 and not s["name"].startswith("??_7")}
        for r in rs:
            if r["status"] != "match":
                continue
            code, rel = funcs[r["symbol"]]
            orig = common.exe().read(r["addr"], len(code))
            for off, name, typ in rel:
                if name in local:
                    continue
                if typ == DIR32:
                    target = u32(orig, off) - s32(code, off)
                elif typ == REL32:
                    target = r["addr"] + off + 4 + s32(orig, off) - s32(code, off)
                else:
                    continue
                if name in derived and derived[name] != target:
                    conflicts.append("%s: %X vs %X" % (name, derived[name], target))
                derived.setdefault(name, target)
    return derived, conflicts


# ---------------------------------------------------------------- patch vtable references

COMDAT = 0x1000


def prepare_obj(obj, out, derived, counter, keep):
    """Copy obj to out with two changes. References to vtables whose game address we know are
    pointed at a new undefined symbol (resolved to the game's vtable). COMDAT sections that nothing
    we keep can reach (our vtable copies, inline functions they pull in) lose their relocations so
    their references don't need resolving. Returns {new symbol: address}."""
    d = bytearray(open(obj, "rb").read())
    secs, syms = common.parse_coff(bytes(d))
    nsym, symptr = u32(d, 12), u32(d, 8)
    byidx = {s["index"]: s for s in syms}
    remap, new = {}, {}
    for s in syms:
        if s["name"].startswith("??_7") and s["section"] > 0 and s["name"] in derived:
            name = "$vt%04X" % counter[0]
            counter[0] += 1
            remap[s["index"]] = nsym + len(new)
            new[name] = derived[s["name"]]
    retargeted = []  # (section number, new symbol index)
    for i in range(len(secs)):
        o = 20 + i * 40
        relptr, nrel = u32(d, o + 24), struct.unpack_from("<H", d, o + 32)[0]
        for k in range(nrel):
            p = relptr + k * 10
            old = u32(d, p + 4)
            if old in remap:
                struct.pack_into("<I", d, p + 4, remap[old])
                retargeted.append((i + 1, remap[old]))
    # keep every non-COMDAT section and the sections of the functions we hook, plus what they reach
    defined_in = {s["name"]: s["section"] for s in syms if s["section"] > 0}
    reach = [i + 1 for i, sec in enumerate(secs) if not sec["chars"] & COMDAT]
    reach += [defined_in[k] for k in keep if k in defined_in]
    seen = set()
    while reach:
        n = reach.pop()
        if n in seen:
            continue
        seen.add(n)
        o = 20 + (n - 1) * 40
        relptr, nrel = u32(d, o + 24), struct.unpack_from("<H", d, o + 32)[0]
        for k in range(nrel):
            s = byidx.get(u32(d, relptr + k * 10 + 4))
            if s and s["name"] in defined_in:
                reach.append(defined_in[s["name"]])
    # associative COMDATs (selection 5, e.g. EH tables) live and die with their parent section
    parent, i = {}, 0
    while i < nsym:
        o = symptr + i * 18
        secnum, cls, naux = struct.unpack_from("<h", d, o + 12)[0], d[o + 16], d[o + 17]
        if cls == 3 and naux and secnum > 0 and d[o + 18 + 14] == 5:
            parent[secnum] = struct.unpack_from("<H", d, o + 18 + 12)[0]
        i += 1 + naux
    grew = True
    while grew:
        grew = False
        for child, par in parent.items():
            if par in seen and child not in seen:
                seen.add(child)
                grew = True
    # unreachable COMDATs lose their relocations: nothing uses them and /OPT:REF drops them
    # (the linker ignores LNK_REMOVE on COMDATs)
    still_used = set()
    for i, sec in enumerate(secs):
        if sec["chars"] & COMDAT and i + 1 not in seen:
            struct.pack_into("<H", d, 20 + i * 40 + 32, 0)
        else:
            still_used |= {si for _, si, _ in sec["relocs"]}
    # the linker still resolves every undefined external in the symbol table, used or not, so the
    # ones nothing references any more become local absolute symbols
    for s in syms:
        if s["section"] == 0 and s["class"] == 2 and s["value"] == 0 and s["index"] not in still_used \
                and s["index"] not in remap:
            o = symptr + s["index"] * 18
            struct.pack_into("<h", d, o + 12, -1)
            d[o + 16] = 3
    # a vtable reference can vanish (an inlined base constructor's store gets optimized away, or
    # its section was stripped): those new symbols become local too, so nothing needs resolving
    used_new = {idx for sec, idx in retargeted if sec in seen or not secs[sec - 1]["chars"] & COMDAT}
    records = b"".join(struct.pack("<8sIhHBB", n.encode(), 0, 0 if nsym + k in used_new else -1, 0,
                                   2 if nsym + k in used_new else 3, 0) for k, n in enumerate(new))
    insert = symptr + nsym * 18
    d[insert:insert] = records
    struct.pack_into("<I", d, 12, nsym + len(new))
    open(out, "wb").write(d)
    return {n: a for k, (n, a) in enumerate(new.items()) if nsym + k in used_new}


# ---------------------------------------------------------------- resolve externals

def undefined_refs(objs):
    """symbol -> set of relocation types, for symbols undefined in every obj."""
    defined, refs = set(), {}
    for obj in objs:
        secs, syms = common.parse_coff(open(obj, "rb").read())
        byidx = {s["index"]: s for s in syms}
        for s in syms:
            if s["section"] > 0 and s["class"] == 2:
                defined.add(s["name"])
        for sec in secs:
            for _, si, typ in sec["relocs"]:
                s = byidx.get(si)
                if s and s["section"] == 0 and s["class"] == 2:
                    refs.setdefault(s["name"], set()).add(typ)
    return {k: v for k, v in refs.items() if k not in defined}


def demangle(name):
    code, out = run(os.path.join(common.CC_BIN, "undname.exe"), name)
    m = re.search(r'is :- "(.*)"', out)
    return m.group(1) if m else name


def resolve(refs, derived, new_abs):
    names = common.name_index()
    manual = {}
    path = os.path.join(common.CONFIG, "externs.csv")
    if os.path.exists(path):
        with open(path) as f:
            for row in csv.reader(f):
                if row and not row[0].startswith("#"):
                    manual[row[0].strip()] = int(row[1], 16)
    resolved, how, left = {}, {}, []
    for sym in sorted(refs):
        if sym in new_abs:
            resolved[sym], how[sym] = new_abs[sym], "game vtable"
            continue
        if sym in derived:
            resolved[sym], how[sym] = derived[sym], "derived from original bytes"
            continue
        m = ADDR_IN_NAME.search(sym)
        if m:
            resolved[sym], how[sym] = int(m.group(1), 16), "address in name"
            continue
        if sym in manual:
            resolved[sym], how[sym] = manual[sym], "config/externs.csv"
            continue
        plain = demangle(sym) if sym.startswith("?") else sym.lstrip("_")
        q = re.search(r"([A-Za-z_][\w:~]*)\s*\(", plain)
        q = q.group(1) if q else plain
        q = re.sub(r"(\w+)::\1$", r"\1::ctor", q)
        q = re.sub(r"(\w+)::~\1$", r"\1::dtor", q)
        key = common.normalize_name(q)
        if key in names:
            resolved[sym], how[sym] = names[key], "yugecin name " + q
            continue
        left.append(sym)
    return resolved, how, left


# ---------------------------------------------------------------- generate asm, link

def asm_header():
    return [".386", ".model flat", "OPTION CASEMAP:NONE", ""]


def write_externs(resolved, refs):
    lines = asm_header()
    data, code = ["_DATA SEGMENT"], ["_TEXT SEGMENT"]
    for i, (sym, addr) in enumerate(sorted(resolved.items())):
        if REL32 in refs.get(sym, ()):
            data.append("$cell_%d DD 0%08Xh" % (i, addr))
            code += ["PUBLIC %s" % sym, "%s PROC" % sym, "\tjmp DWORD PTR $cell_%d" % i, "%s ENDP" % sym]
        else:
            lines += ["PUBLIC %s" % sym, "%s EQU 0%08Xh" % (sym, addr)]
    lines += [""] + data + ["_DATA ENDS", ""] + code + ["_TEXT ENDS", "END"]
    open(os.path.join(OUT, "externs.asm"), "w").write("\n".join(lines) + "\n")


def write_hooks(hooks):
    lines = asm_header()
    lines += ["EXTERN %s:NEAR" % h["symbol"] for h in hooks]
    lines += ["", "_DATA SEGMENT", "PUBLIC _nfsu2_hooks", "_nfsu2_hooks LABEL DWORD"]
    for i, h in enumerate(hooks):
        size = common.functions()[h["addr"]]["size"]
        first = common.exe().read(h["addr"], 8)
        lines.append("\tDD 0%08Xh, %s, %d" % (h["addr"], h["symbol"], size))
        lines.append("\tDB " + ", ".join("0%02Xh" % b for b in first))
        crc = zlib.crc32(common.exe().read(h["addr"], size)) & 0xFFFFFFFF
        lines.append("\tDD $name_%d, 0%08Xh" % (i, crc))
    lines += ["\tDD 0, 0, 0", "\tDB 8 DUP (0)", "\tDD 0, 0"]
    for i, h in enumerate(hooks):
        name = (common.functions()[h["addr"]]["name"] or "sub_%X" % h["addr"]).replace('"', "")
        lines.append('$name_%d DB "%s", 0' % (i, name))
    lines += ["_DATA ENDS", "END"]
    open(os.path.join(OUT, "hooks.asm"), "w").write("\n".join(lines) + "\n")


# ---------------------------------------------------------------- verify the built DLL

def read_map(path):
    syms = {}
    for line in open(path, encoding="latin1"):
        m = re.match(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})", line)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    return syms


def verify(dll_path, map_path, hooks):
    dll = common.Exe(dll_path)
    syms = read_map(map_path)
    cells = {}
    for sym, va in syms.items():
        code = dll.read(va, 6)
        if code[:2] == b"\xff\x25":
            cells[va] = u32(dll.read(u32(code, 2), 4))
    problems = []
    replaced = {syms[h["symbol"]]: h["addr"] for h in hooks}
    # our own matched copies of functions the hook table can't name (static helpers): calling ours
    # is calling a byte-identical copy of the original
    results = json.load(open(os.path.join(common.BUILD, "results.json")))
    own_copies = {(r["symbol"], r["addr"]) for r in results if r.get("status") == "match" and r.get("symbol")}
    for h in hooks:
        va = syms[h["symbol"]]
        size = common.functions()[h["addr"]]["size"]
        code, rel = common.coff_functions(h["obj"])[h["symbol"]]
        if len(code) > size and any(off >= size for off, _, _ in rel):
            size = len(code)  # a jump table after the code, as in common.compare
        mine, orig = dll.read(va, size), common.exe().read(h["addr"], size)
        fields = {off for off, _, _ in rel}
        diffs = [k for k in range(size) if mine[k] != orig[k]]
        for k in diffs:
            if not any(f <= k < f + 4 for f in fields):
                problems.append("%X: byte %d differs outside a relocated field" % (h["addr"], k))
                break
        for off, name, typ in rel:
            if typ == DIR32:
                t_mine, t_orig = u32(mine, off), u32(orig, off)
            elif typ == REL32:
                t_mine, t_orig = va + off + 4 + s32(mine, off), h["addr"] + off + 4 + s32(orig, off)
            else:
                continue
            t_mine = cells.get(t_mine, t_mine)
            if t_mine == t_orig or replaced.get(t_mine) == t_orig:
                continue
            if 0 <= t_mine - va < size and t_mine - va == t_orig - h["addr"]:
                continue  # inside the function itself (a jump table and its cases)
            if (name, t_orig) in own_copies:
                continue
            if name.startswith("__ehhandler$"):
                continue  # each recompiled function registers its own exception handler and tables
            # our own copy of a string literal or floating-point constant: compare contents
            a, b = dll.read(t_mine, 256), common.exe().read(t_orig, 256)
            n = 0
            if name.startswith("??_C@") and b"\0" in a:
                n = a.index(b"\0") + 1
            elif name.startswith("__real@"):
                n = (len(name) - len("__real@")) // 2
            if n and a[:n] == b[:n]:
                continue
            problems.append("%X+%X: %s reaches %X, original reaches %X" % (h["addr"], off, name, t_mine, t_orig))
    return problems


def build(install=False, include_equivalent=False):
    results = json.load(open(os.path.join(common.BUILD, "results.json")))
    os.makedirs(OUT, exist_ok=True)
    chosen, excluded = select(results, include_equivalent)
    derived, conflicts = derive(chosen)
    if conflicts:
        sys.exit("conflicting derived addresses:\n  " + "\n  ".join(conflicts))
    while True:
        counter, new_abs, objs = [1], {}, []
        for obj in chosen:
            out = os.path.join(OUT, "obj", os.path.basename(obj))
            os.makedirs(os.path.dirname(out), exist_ok=True)
            keep = [r["symbol"] for r in chosen[obj]]
            new_abs.update(prepare_obj(obj, out, derived, counter, keep))
            objs.append(out)
        refs = undefined_refs(objs)
        resolved, how, left = resolve(refs, derived, new_abs)
        hooks = [dict(r, obj=o) for o in chosen for r in chosen[o]]
        write_externs(resolved, refs)
        write_hooks(hooks)
        for asm in ("externs.asm", "hooks.asm"):
            code, out = run(os.path.join(common.CC_BIN, "ml.exe"), "/nologo", "/c", "/coff", asm)
            if code:
                sys.exit(out)
        ok, out = common.compile_cpp(os.path.join(common.ROOT, "loader", "loader.cpp"),
                                     os.path.join(OUT, "loader.obj"), "game_noeh")
        if not ok:
            sys.exit(out)
        code, out = run(os.path.join(common.CC_BIN, "link.exe"), "/nologo", "/DLL", "/OUT:nfsu2decomp.asi",
                        "/MAP:nfsu2decomp.map", "/OPT:REF", "/BASE:0x2F000000", *objs,
                        "loader.obj", "hooks.obj", "externs.obj", "kernel32.lib")
        # LNK2001/2019 print either _name or "readable name" (?mangled)
        missing = {m[0] or m[1] for m in re.findall(
            r'unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))', out)}
        if code and missing:
            # drop the objects that need something we cannot provide, then try again
            before = len(chosen)
            for obj in list(chosen):
                needs = set(undefined_refs([os.path.join(OUT, "obj", os.path.basename(obj))])) & missing
                if needs:
                    for r in chosen.pop(obj):
                        excluded.append((r["addr"], r["file"], "needs " + ", ".join(sorted(needs))))
            if chosen and len(chosen) < before:
                continue
        if code:
            sys.exit(out)
        break
    problems = verify(os.path.join(OUT, "nfsu2decomp.asi"), os.path.join(OUT, "nfsu2decomp.map"), hooks)
    print("hooked functions: %d" % len(hooks))
    for h in sorted(hooks, key=lambda h: h["addr"]):
        print("  %06X  %s" % (h["addr"], h["file"]))
    print("not hooked: %d" % len(excluded))
    for a, f, why in sorted(excluded):
        print("  %06X  %s  -- %s" % (a, f, why))
    print("game references: %d (%s)" % (len(resolved), ", ".join(
        "%d %s" % (sum(1 for v in how.values() if v.startswith(k)), k)
        for k in ("derived", "game vtable", "address in name", "yugecin", "config"))))
    if left:
        print("left to the C runtime: " + ", ".join(left))
    if problems:
        print("VERIFY FAILED:\n  " + "\n  ".join(problems))
        sys.exit(1)
    print("verified: every hooked function is byte-identical to the original and reaches the same targets")
    print("built " + os.path.join(OUT, "nfsu2decomp.asi"))
    if install:
        dest = os.path.join(common.PATHS["game_dir"], "scripts", "zz_nfsu2decomp.asi")
        shutil.copyfile(os.path.join(OUT, "nfsu2decomp.asi"), dest)
        print("installed to " + dest)


if __name__ == "__main__":
    build(install="--install" in sys.argv, include_equivalent="--equivalent" in sys.argv)
