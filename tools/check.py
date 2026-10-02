"""Compile every source file and check each annotated function against the original exe.

  python tools/check.py                 check everything under src/
  python tools/check.py src/game/x.cpp  check some files
  python tools/check.py --diff 43B380   show an aligned diff for one function
  python tools/check.py --try DIR       check files without saving results (add --diff ADDR for a diff)

Source annotations (comments directly above a function definition):
  // PROFILE: game            once per file; a key of config/profiles.json (default: game)
  // FUNCTION: 0x0043B380     the original address of the function that follows
      optional on the same line:  SYMBOL=<mangled name>  EQUIVALENT  NOHOOK

Jumbo files: a .cpp that #includes other .cpp files is compiled as one unit, the way EA built the
game (the z*.cpp source lists in the Most Wanted decomp). Functions in the same unit can be inlined
into each other and the compiler knows what registers they use, so some functions only match there.
The included files keep their annotations; checking one of them checks its whole jumbo file. The
jumbo's own PROFILE line applies to everything in it.
"""
import difflib, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

SRC = os.path.join(common.ROOT, "src")
OBJ = os.path.join(common.BUILD, "obj")


JUMBO_INCLUDE = re.compile(r'^\s*#include\s+"([^"]+\.cpp)"', re.M)


def jumbo_parts(path):
    """The .cpp files a jumbo file includes, in order (empty for an ordinary file)."""
    text = open(path, encoding="latin1").read()
    return [os.path.normpath(os.path.join(os.path.dirname(path), m)) for m in JUMBO_INCLUDE.findall(text)]


def walk_cpp(top):
    out = []
    for root, _, files in os.walk(top):
        out += [os.path.join(root, f) for f in files if f.endswith(".cpp")]
    return out


def source_files(args):
    out = []
    for a in [os.path.abspath(x) for x in args] or [SRC]:
        out += walk_cpp(a) if os.path.isdir(a) else [a]
    # a file included by a jumbo file is checked through the jumbo file
    owner = {}
    for f in set(walk_cpp(SRC)) | set(out):
        for part in jumbo_parts(f):
            owner[os.path.normcase(part)] = f
    picked = []
    for f in out:
        f = owner.get(os.path.normcase(os.path.normpath(f)), f)
        if f not in picked:
            picked.append(f)
    return sorted(picked)


def mangled_prefix(qualified):
    parts = [p for p in qualified.split("::") if p]
    fname, scopes = parts[-1], parts[:-1]
    scope = "@".join(reversed(scopes))
    if scopes and fname == scopes[-1]:
        return "??0" + scope + "@@"
    if fname.startswith("~"):
        return "??1" + scope + "@@"
    return "?" + fname + ("@" + scope if scope else "") + "@@"


def annotations(path):
    """(profile, annotations); each annotation records the file it is in (for jumbo files, the
    included file)."""
    parts = jumbo_parts(path)
    if parts:
        profile, _ = annotations_in(path)
        found = []
        for part in parts:
            found += annotations_in(part)[1]
        return profile, found
    return annotations_in(path)


def annotations_in(path):
    lines = open(path, encoding="latin1").read().splitlines()
    profile = "game"
    for l in lines:
        m = re.match(r"\s*//\s*PROFILE:\s*(\w+)", l)
        if m:
            profile = m.group(1)
            break
    found = []
    for i, l in enumerate(lines):
        m = re.match(r"\s*//\s*FUNCTION:\s*(?:0x)?([0-9A-Fa-f]+)(.*)", l)
        if not m:
            continue
        opts = m.group(2)
        sym = re.search(r"SYMBOL=(\S+)", opts)
        qualified = None
        if not sym:
            text = ""
            for nxt in lines[i + 1:i + 8]:
                if nxt.strip().startswith("//"):
                    continue
                text += " " + nxt
                if "(" in text:
                    break
            head = text.split("(")[0].strip()
            qualified = re.split(r"[\s\*&]+", head)[-1] if head else None
        found.append({"addr": int(m.group(1), 16), "line": i + 1, "src": path,
                      "symbol": sym.group(1) if sym else None, "qualified": qualified,
                      "equivalent": "EQUIVALENT" in opts, "nohook": "NOHOOK" in opts})
    return profile, found


def pick_symbol(ann, funcs):
    if ann["symbol"]:
        return ann["symbol"] if ann["symbol"] in funcs else None, "symbol %s not in object" % ann["symbol"]
    if not ann["qualified"]:
        return None, "could not find the function name after the annotation"
    prefix = mangled_prefix(ann["qualified"])
    cands = [n for n in funcs if n.startswith(prefix)]
    if not cands:
        cands = [n for n in funcs if n == "_" + ann["qualified"].split("::")[-1]]
    if len(cands) == 1:
        return cands[0], None
    if not cands:
        return None, "no compiled function for %s (looked for %s...)" % (ann["qualified"], prefix)
    return None, "several overloads of %s; add SYMBOL=" % ann["qualified"]


def check(files):
    results = []
    for path in files:
        rel = os.path.relpath(path, common.ROOT)
        profile, anns = annotations(path)
        obj = os.path.join(OBJ, os.path.splitext(os.path.relpath(path, SRC))[0] + ".obj")
        ok, out = common.compile_cpp(path, obj, profile)
        if not ok:
            errs = [l for l in out.splitlines() if "error" in l][:3]
            for a in anns:
                results.append(dict(a, file=os.path.relpath(a.pop("src"), common.ROOT), profile=profile,
                                    status="compile-error", similarity=0,
                                    note=" / ".join(errs)))
            continue
        funcs = common.coff_functions(obj)
        for a in anns:
            sym, err = pick_symbol(a, funcs)
            r = dict(a, file=os.path.relpath(a.pop("src"), common.ROOT), obj=obj, profile=profile, symbol=sym)
            if not sym:
                r.update(status="error", similarity=0, note=err)
            else:
                code, rel_ = funcs[sym]
                matched, sim, _ = common.compare(a["addr"], code, rel_)
                if matched:
                    bad = common.literal_mismatches(a["addr"], code, rel_, common.coff_literals(obj))
                    if bad:
                        matched, r["note"] = False, "code matches but " + "; ".join(bad)
                r.update(status="match" if matched else ("equivalent" if a["equivalent"] else "nonmatching"),
                         similarity=round(sim, 4), size=len(code))
            results.append(r)
    return results


def progress(results):
    done = {r["addr"]: r["status"] for r in results}
    rows = []
    for lo, hi, label, scope in common.REGIONS:
        fs = [(a, s["size"]) for a, s in common.functions().items() if lo <= a < hi]
        n, b = len(fs), sum(s for _, s in fs)
        m = [(a, s) for a, s in fs if done.get(a) == "match"]
        e = [(a, s) for a, s in fs if done.get(a) == "equivalent"]
        rows.append((label, scope, n, b, len(m), sum(s for _, s in m), len(e), sum(s for _, s in e)))
    return rows


def report(results):
    order = {"match": 0, "equivalent": 1, "nonmatching": 2, "error": 3, "compile-error": 4}
    for r in sorted(results, key=lambda r: (order[r["status"]], r["addr"])):
        extra = "" if r["status"] == "match" else ("  %.0f%%" % (100 * r["similarity"]) if r.get("similarity") else "")
        print("  %06X  %-13s%s  %s%s" % (r["addr"], r["status"], extra, r["file"],
                                          ("  -- " + r["note"]) if r.get("note") else ""))
    rows = progress(results)
    md = ["# Progress", "", "Generated by `tools/check.py`. Bytes are function sizes from the IDA export.", "",
          "| Region | Scope | Functions | Matched | Equivalent | Matched bytes |", "|---|---|---|---|---|---|"]
    for label, scope, n, b, mn, mb, en, eb in rows:
        md.append("| %s | %s | %d | %d | %d | %.2f%% of %.0f KB |" % (label, scope, n, mn, en, 100 * mb / max(b, 1), b / 1024))
    counts = {s: sum(r["status"] == s for r in results) for s in order}
    md += ["", "Checked: " + ", ".join("%d %s" % (v, k) for k, v in counts.items() if v)]
    os.makedirs(os.path.join(common.ROOT, "reports"), exist_ok=True)
    open(os.path.join(common.ROOT, "reports", "progress.md"), "w").write("\n".join(md) + "\n")
    with open(os.path.join(common.BUILD, "results.json"), "w") as f:
        json.dump(results, f, indent=1)
    game = [r for r in rows if r[0] == "game"][0]
    print("\n%s" % md[-1])
    print("game region: %d/%d functions matched (%.3f%% of bytes), %d equivalent" % (
        game[4], game[2], 100 * game[5] / game[3], game[6]))


def diff(addr, results=None):
    if results is None:
        results = json.load(open(os.path.join(common.BUILD, "results.json")))
    r = [x for x in results if x["addr"] == addr]
    if not r or not r[0].get("symbol"):
        sys.exit("run check.py first; no compiled result for %X" % addr)
    code, rel = common.coff_functions(r[0]["obj"])[r[0]["symbol"]]
    size = common.functions()[addr]["end"] - addr
    theirs = common.exe().read(addr, size)
    mine_n = common.normalized(common.with_reloc_sentinels(code, rel))
    theirs_n = common.normalized(theirs)
    a = ["%s %s" % (i.mnemonic, i.op_str) for i, _ in mine_n]
    b = ["%s %s" % (i.mnemonic, i.op_str) for i in common.disasm(theirs, addr)]
    sm = difflib.SequenceMatcher(None, [s for _, s in mine_n], [s for _, s in theirs_n], autojunk=False)
    print("%X  %s  mine %d bytes, original %d bytes" % (addr, r[0]["symbol"], len(code), size))
    for op, a1, a2, b1, b2 in sm.get_opcodes():
        for k in range(max(a2 - a1, b2 - b1)):
            x = a[a1 + k] if a1 + k < a2 else ""
            y = b[b1 + k] if b1 + k < b2 else ""
            print(" %s %-44s | %s" % ("  " if op == "equal" else "!!", x, y))


if __name__ == "__main__":
    args = sys.argv[1:]
    if args[:1] == ["--diff"]:
        diff(int(args[1], 16))
    elif args[:1] == ["--try"]:
        # compile and compare without touching the saved results (for trying source variants);
        # "--try <files or dirs> --diff 43B380" also prints the diff for one address
        want = None
        if "--diff" in args:
            k = args.index("--diff")
            want, args = int(args[k + 1], 16), args[:k] + args[k + 2:]
        tried = check(source_files(args[1:]))
        if want is not None:
            diff(want, [r for r in tried if r["addr"] == want][-1:])
            sys.exit(0)
        for r in tried:
            print("  %06X  %-12s %3.0f%%  %s%s" % (r["addr"], r["status"], 100 * r.get("similarity", 0), r["file"],
                                                 ("  -- " + r["note"]) if r.get("note") else ""))
    else:
        files = source_files(args)
        results = check(files)
        saved = os.path.join(common.BUILD, "results.json")
        if args and os.path.exists(saved):
            # a partial run replaces the saved results for the files it checked
            done = {os.path.relpath(f, common.ROOT) for f in files} | {r["file"] for r in results}
            results += [r for r in json.load(open(saved)) if r["file"] not in done
                        and os.path.exists(os.path.join(common.ROOT, r["file"]))]
        report(results)
