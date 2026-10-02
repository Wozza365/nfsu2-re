"""Generate C++ class headers from yugecin's IDA export, as a starting point for hand editing.

  python tools/gen_class.py Career CareerStage      writes include/game/Career.h etc.
  python tools/gen_class.py Career --force          overwrite an existing header

Each header has the exact layout from the IDA struct (checked at compile time: size and every field
offset), and a method declaration for every function yugecin named <Class>::<name>, using his
prototype where it can be expressed. Headers for structs embedded by value are generated too.
include/game/common.h (forward declarations of every struct, all enums) is regenerated every run.
Existing class headers are never overwritten without --force: they are meant to be edited.
"""
import json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

MODEL = json.load(open(os.path.join(common.CONFIG, "ida_model.json")))
STRUCTS, ENUMS = MODEL["structs"], MODEL["enums"]
OUT = os.path.join(common.ROOT, "include", "game")
KEYWORDS = set("""auto bool break case catch char class const continue default delete do double else enum explicit
extern false float for friend goto if inline int long mutable namespace new operator private protected public
register return short signed sizeof static struct switch template this throw true try typedef typename union
unsigned using virtual void volatile while wchar_t interface""".split())
BASIC = {"char", "signed char", "unsigned char", "short", "unsigned short", "int", "unsigned int", "long",
         "unsigned long", "float", "double", "bool", "void", "__int64", "unsigned __int64"}
MAP = {"_BYTE": "unsigned char", "_WORD": "unsigned short", "_DWORD": "unsigned int", "BYTE": "unsigned char",
       "WORD": "unsigned short", "DWORD": "unsigned long", "BOOL": "int", "wchar_t": "unsigned short",
       "__int8": "char", "unsigned __int8": "unsigned char", "__int16": "short", "unsigned __int16": "unsigned short",
       "__int32": "int", "unsigned __int32": "unsigned int", "_QWORD": "unsigned __int64", "_BOOL1": "bool",
       "_BOOL4": "int", "size_t": "unsigned int"}
ALIGN = {"char": 1, "unsigned char": 1, "bool": 1, "short": 2, "unsigned short": 2, "double": 8,
         "__int64": 8, "unsigned __int64": 8}


def ident(n):
    n = re.sub(r"[^A-Za-z0-9_]", "_", n)
    if not n or n[0].isdigit():
        n = "_" + n
    return n + "_" if n in KEYWORDS else n


# ---------------------------------------------------------------- layout

_align = {}


def field_align(f):
    if f["decl"].rstrip().endswith("*"):
        return 4
    if f["struct"]:
        return struct_align(f["struct"])
    base = f["decl"].strip()
    return ALIGN.get(base, 4 if base not in ENUMS else 4)


def needs_pack(name):
    s = STRUCTS[name]
    a = struct_align_natural(name)
    if s["size"] % a:
        return True
    for f in s["fields"]:
        if f["off"] % field_align(f):
            return True
    return False


def struct_align_natural(name):
    s = STRUCTS[name]
    al = [field_align(f) for f in s["fields"]]
    if s["base"]:
        al.append(struct_align(s["base"]))
    return max(al or [1])


def struct_align(name):
    if name not in _align:
        _align[name] = 1  # guards recursion
        _align[name] = 1 if needs_pack(name) else struct_align_natural(name)
    return _align[name]


# ---------------------------------------------------------------- prototypes

def c_type(t):
    """IDA type string -> C++ type, or None when it can't be expressed simply."""
    t = re.sub(r"\b(struct|union|enum|const|volatile)\s+", "", t).strip()
    m = re.match(r"^([A-Za-z_][A-Za-z0-9_ ]*?)\s*(\*+)?$", t)
    if not m:
        return None
    base, ptr = m.group(1).strip(), m.group(2) or ""
    base = MAP.get(base, base)
    if base not in BASIC and base not in STRUCTS and base not in ENUMS:
        if not ptr:
            return None
        base = "void"
    return base + (" " + ptr if ptr else "")


def split_params(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def declaration(cls, method, proto, addr):
    """Return (declaration line, error) for a method."""
    m = re.match(r"^(.*?)\s*\b(__thiscall|__cdecl|__stdcall|__fastcall|__usercall|__userpurge)\s+[\w:@?$]+\s*\((.*)\)\s*;?\s*$", proto)
    if not m:
        return None, "unreadable prototype"
    ret, cc, params = m.group(1), m.group(2), split_params(m.group(3))
    if cc in ("__usercall", "__userpurge", "__fastcall"):
        return None, cc + " can't be written in C++"
    if params == ["void"]:
        params = []
    if cc == "__thiscall":
        params = params[1:]
    args = []
    for i, p in enumerate(params):
        if p == "...":
            args.append("...")
            continue
        if "(" in p:
            nm = re.search(r"\*\s*(\w+)\s*\)", p)
            args.append("void *" + ident(nm.group(1) if nm else "a%d" % (i + 1)))
            continue
        pm = re.match(r"^(.*?)([A-Za-z_]\w*)$", p)
        tstr, name = (pm.group(1), pm.group(2)) if pm else (p, "")
        if not tstr.strip() or name in BASIC or MAP.get(name) or name in ("unsigned", "signed"):
            tstr, name = p, ""
        ct = c_type(tstr)
        if ct is None:
            return None, "parameter type %r" % tstr
        name = ident(name) if name else "a%d" % (i + 1)
        args.append(ct + ("" if ct.endswith("*") else " ") + name)
    if method == "ctor":
        return "%s(%s);" % (cls, ", ".join(args)), None
    if method == "dtor":
        return "~%s();" % cls, None
    rt = c_type(ret) if ret.strip() else "void"
    if rt is None:
        return None, "return type %r" % ret
    static = "static " if cc != "__thiscall" else ""
    conv = "__stdcall " if cc == "__stdcall" else ""
    return "%s%s%s%s%s(%s);" % (static, rt, "" if rt.endswith("*") else " ", conv, method, ", ".join(args)), None


def methods(cls):
    out, seen = [], set()
    for a, f in sorted(common.functions().items()):
        n = f["name"].lstrip("?")
        if not n.startswith(cls + "::"):
            continue
        raw = n[len(cls) + 2:].rstrip("?")
        method = raw if raw in ("ctor", "dtor") else ident(raw)
        if re.fullmatch(r"_?[0-9A-F]{6}", method):
            method = "sub_" + method.lstrip("_")
        if method in seen and method not in ("ctor", "dtor"):
            method = "%s_%X" % (method, a)
        seen.add(method)
        decl, err = declaration(cls, method, f["type"], a) if f["type"] else (None, "no prototype")
        out.append((a, f["name"], decl, err, f["comment"]))
    return out


# ---------------------------------------------------------------- headers

def write_common():
    lines = ["// Generated by tools/gen_class.py: forward declarations of every IDA struct and all IDA enums.",
             "// Do not edit; regenerated on every run.", "#ifndef GAME_COMMON_H", "#define GAME_COMMON_H", "",
             "#include <stddef.h>", ""]
    for e, vals in sorted(ENUMS.items()):
        body = ", ".join("%s = 0x%X" % (n, v) for n, v in vals) or "%s__none" % e
        lines.append("enum %s { %s };" % (e, body))
    lines.append("")
    lines += ["%s %s;" % (s["kind"], n) for n, s in sorted(STRUCTS.items())]
    lines += ["", "// hand-written declarations shared by game code", '#include "game/shared.h"', "", "#endif"]
    os.makedirs(OUT, exist_ok=True)
    open(os.path.join(OUT, "common.h"), "w").write("\n".join(lines) + "\n")


def write_class(name, force, done):
    if name in done:
        return
    done.add(name)
    s = STRUCTS[name]
    deps = sorted({f["struct"] for f in s["fields"] if f["struct"]} | ({s["base"]} if s["base"] else set()))
    for d in deps:
        write_class(d, False, done)
    path = os.path.join(OUT, name + ".h")
    if os.path.exists(path) and not force:
        return
    packed = needs_pack(name)
    guard = "GAME_%s_H" % name.upper()
    lines = ["// %s: 0x%X bytes. Layout from yugecin's IDA struct, methods from his names and prototypes." % (name, s["size"]),
             "// Generated by tools/gen_class.py as a starting point; edit freely (it won't be overwritten).",
             "#ifndef " + guard, "#define " + guard, "", '#include "game/common.h"']
    lines += ['#include "game/%s.h"' % d for d in deps]
    lines.append("")
    if packed:
        lines.append("#pragma pack(push, 1)  // the IDA layout isn't naturally aligned")
    lines.append("%s %s%s {" % (s["kind"], name, " : " + s["base"] if s["base"] else ""))
    pos = STRUCTS[s["base"]]["size"] if s["base"] else 0
    for f in s["fields"]:
        if s["kind"] == "struct" and f["off"] > pos:
            lines.append("\tunsigned char _pad_%X[0x%X];" % (pos, f["off"] - pos))
        lines.append("\t%s%s%s;%s" % (f["decl"], f["name"], f["dims"], ("  // " + f["note"]) if f["note"] else ""))
        pos = max(pos, f["off"] + f["size"])
    if s["kind"] == "struct" and pos < s["size"]:
        lines.append("\tunsigned char _pad_%X[0x%X];" % (pos, s["size"] - pos))
    ms = methods(name) if s["kind"] == "struct" else []
    if ms:
        lines += ["", "\t// methods: address and yugecin's name"]
        for a, full, decl, err, cmt in ms:
            if decl:
                lines.append("\t%-60s // %06X %s" % (decl, a, full))
            else:
                lines.append("\t// %06X %s: not declared, %s" % (a, full, err))
    lines.append("};")
    if packed:
        lines.append("#pragma pack(pop)")
    if s["size"]:
        lines.append("typedef char _size_check_%s[sizeof(%s) == 0x%X ? 1 : -1];" % (name, name, s["size"]))
    if s["kind"] == "struct":
        for f in s["fields"]:
            lines.append("typedef char _off_%s_%s[offsetof(%s, %s) == 0x%X ? 1 : -1];" % (name, f["name"], name, f["name"], f["off"]))
    lines += ["", "#endif"]
    open(path, "w").write("\n".join(lines) + "\n")
    print("wrote " + os.path.relpath(path, common.ROOT) + (" (packed)" if packed else ""))


if __name__ == "__main__":
    force = "--force" in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith("--")]
    write_common()
    done = set()
    for n in names:
        if n not in STRUCTS:
            sys.exit("no IDA struct named " + n)
        write_class(n, force, done)
    # compile check: every generated header on its own
    for n in sorted(done):
        test = os.path.join(common.BUILD, "hdr_%s.cpp" % n)
        open(test, "w").write('#include "game/%s.h"\n' % n)
        ok, out = common.compile_cpp(test, test[:-4] + ".obj", "game", ["/Zs"])
        os.remove(test)
        if not ok:
            print("COMPILE FAILED for %s:\n%s" % (n, "\n".join(l for l in out.splitlines() if "error" in l)[:1500]))
