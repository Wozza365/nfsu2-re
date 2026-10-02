"""Which field is at an offset? Walks into embedded structs and arrays.

  python tools/layout.py Career 7138 713C 78EC     ->  Career+7138 = field_7138 (unsigned char) ...
  python tools/layout.py Career                    ->  the whole top-level layout
"""
import json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

S = json.load(open(os.path.join(common.CONFIG, "ida_model.json")))["structs"]


def elem_size(f):
    n = 1
    for d in re.findall(r"\[(\d+)\]", f["dims"]):
        n *= int(d)
    return f["size"] // n, n


def resolve(name, off, path=""):
    s = S[name]
    if s["base"] and off < S[s["base"]]["size"]:
        return resolve(s["base"], off, path)
    for f in s["fields"]:
        if f["off"] <= off < f["off"] + f["size"]:
            rel = off - f["off"]
            esz, n = elem_size(f)
            idx, inner = divmod(rel, esz) if n > 1 else (None, rel)
            p = path + ("." if path else "") + f["name"] + ("[%d]" % idx if idx is not None else "")
            if f["struct"] and f["struct"] in S:
                return resolve(f["struct"], inner, p)
            t = (f["decl"] + f["dims"]).strip()
            return p + (" +0x%X" % inner if inner else "") + "  (%s)" % t
    return "%s+0x%X: no field (padding)" % (path or name, off)


if __name__ == "__main__":
    name = sys.argv[1]
    if len(sys.argv) == 2:
        s = S[name]
        print("%s: 0x%X bytes%s" % (name, s["size"], ", base " + s["base"] if s["base"] else ""))
        for f in s["fields"]:
            print("  %5X  %s%s%s%s" % (f["off"], f["decl"], f["name"], f["dims"], ("  // " + f["note"][:70]) if f["note"] else ""))
    for o in sys.argv[2:]:
        print("%s+%s = %s" % (name, o.upper(), resolve(name, int(o, 16))))
