"""Generate config/symbols.csv and include/ida/ida_types.h from yugecin's IDA export (ref/SPEED2.idc).

symbols.csv: every function (with size, region, name, prototype, comment) and every named data item.
ida_types.h: the IDA structs and enums as C++ declarations with explicit padding, so offsets match the
game exactly. Member types come from IDA's type strings where they can be expressed safely, and fall
back to plain sized types otherwise. Every struct gets a compile-time size check.
"""
import csv, os, re, sys
from collections import defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

IDC = os.path.join(common.ROOT, common.PATHS["idc"])
t = open(IDC, encoding="latin1").read()
STR = r'"((?:[^"\\]|\\.)*)"'
HEX = r"(-?0[Xx][0-9A-Fa-f]+|-?\d+)"


def num(s):
    return int(s, 0) if s.lower().startswith(("0x", "-0x")) else int(s)


def unescape(s):
    return s.replace('\\"', '"').replace("\\n", " ").replace("\\\\", "\\")


# ---------------------------------------------------------------- symbols.csv

funcs = {int(a, 16): int(b, 16) for a, b in re.findall(r"add_func\s*\(0X([0-9A-F]+),0X([0-9A-F]+)\)", t)}
names = {int(a, 16): n for a, n in re.findall(r"set_name\s*\(0X([0-9A-F]+),\s*" + STR, t)}
types = {int(a, 16): unescape(ty) for a, ty in re.findall(r"(?:SetType|apply_type)\s*\(0X([0-9A-F]+),\s*" + STR, t)}
fcmts = {int(a, 16): unescape(c) for a, c in re.findall(r"set_func_cmt\s*\(0X([0-9A-F]+),\s*" + STR, t)}
AUTO = re.compile(r"^(sub|loc|locret|def|jpt|nullsub|j_sub|unk|byte|word|dword|qword|off|flt|dbl|stru|asc|algn|a[A-Z0-9])_")

rows = []
for a in sorted(funcs):
    rows.append({"kind": "func", "addr": "%X" % a, "end": "%X" % funcs[a], "size": funcs[a] - a,
                 "region": common.region_of(a), "name": names.get(a, ""), "type": types.get(a, ""),
                 "comment": fcmts.get(a, "")[:200]})
for a in sorted(names):
    if a in funcs or AUTO.match(names[a]) or common.region_of(a) != "other" and a < 0x783000:
        continue
    rows.append({"kind": "data", "addr": "%X" % a, "end": "", "size": "", "region": "data",
                 "name": names[a], "type": types.get(a, ""), "comment": ""})
with open(os.path.join(common.CONFIG, "symbols.csv"), "w", newline="") as f:
    w = csv.DictWriter(f, fieldnames=["kind", "addr", "end", "size", "region", "name", "type", "comment"])
    w.writeheader()
    w.writerows(rows)
nf = sum(r["kind"] == "func" for r in rows)
print("symbols.csv: %d functions (%d named), %d named data items" % (
    nf, sum(1 for r in rows if r["kind"] == "func" and r["name"] and not AUTO.match(r["name"])), len(rows) - nf))

# ---------------------------------------------------------------- structs and enums

KEYWORDS = set("""auto bool break case catch char class const continue default delete do double else enum explicit
extern false float for friend goto if inline int long mutable namespace new operator private protected public
register return short signed sizeof static struct switch template this throw true try typedef typename union
unsigned using virtual void volatile while wchar_t interface""".split())


def ident(n):
    n = re.sub(r"[^A-Za-z0-9_]", "_", n)
    if not n or n[0].isdigit():
        n = "_" + n
    return n + "_" if n in KEYWORDS else n


struct_kind = {n: (num(u) & 1) for n, u in re.findall(r"add_struc\s*\(-1,\s*" + STR + r",\s*" + HEX + r"\)", t)}
members = defaultdict(list)       # struct -> [(off, name, flags, typeref, size)]
mtypes, mcmts = {}, {}
cur = None
for line in t.splitlines():
    m = re.match(r'\s*id = get_struc_id\(' + STR + r'\);', line)
    if m:
        cur = m.group(1)
        continue
    m = re.match(r'\s*id = add_enum\(', line)
    if m:
        cur = None
        continue
    if cur is None:
        continue
    m = re.match(r'\s*mid = add_struc_member\((.*)\);\s*$', line)
    if m:
        # id, "name", offset, flags, typeid, size[, refinfo target, tdelta, reftype]
        args = [a.strip() for a in re.findall(r'"(?:[^"\\]|\\.)*"|get_\w+\("(?:[^"\\]|\\.)*"\)|[^,]+', m.group(1))]
        name, off, flags, tref, size = args[1].strip('"'), num(args[2]), num(args[3]) & 0xFFFFFFFF, args[4], num(args[5])
        r = re.match(r'get_(struc_id|enum)\(' + STR + r'\)', tref)
        members[cur].append((off, name, flags, (r.group(1), r.group(2)) if r else None, size))
        continue
    m = re.match(r'\s*SetType\(get_member_id\(id,\s*' + HEX + r'\),\s*' + STR + r'\);', line)
    if m:
        mtypes[(cur, num(m.group(1)))] = unescape(m.group(2))
        continue
    m = re.match(r'\s*set_member_cmt\(id,\s*' + HEX + r',\s*' + STR, line)
    if m:
        mcmts[(cur, num(m.group(1)))] = unescape(m.group(2))

enums = {}
for m in re.finditer(r'id = add_enum\(-1,' + STR + r',\s*' + HEX + r'\);(.*?)(?=\n\s*id = |\n\})', t, re.S):
    vals = re.findall(r'add_enum_member\(id,' + STR + r',\s*' + HEX + r',', m.group(3))
    enums[m.group(1)] = [(n, num(v)) for n, v in vals]

for s in struct_kind:
    if struct_kind[s]:  # IDA numbers union members by index; they all live at offset 0
        members[s] = [(0, n, fl, tr, sz) for _, n, fl, tr, sz in members[s]]
size_of = {s: max([o + sz for o, _, _, _, sz in members[s]] or [0]) for s in struct_kind}
ENUM_NAMES = {ident(e) for e in enums}
BASIC = {"char": 1, "signed char": 1, "unsigned char": 1, "__int8": 1, "unsigned __int8": 1, "_BYTE": 1,
         "BYTE": 1, "bool": 1, "short": 2, "unsigned short": 2, "__int16": 2, "unsigned __int16": 2,
         "_WORD": 2, "WORD": 2, "wchar_t": 2, "int": 4, "unsigned int": 4, "__int32": 4,
         "unsigned __int32": 4, "long": 4, "unsigned long": 4, "_DWORD": 4, "DWORD": 4, "BOOL": 4,
         "float": 4, "double": 8, "__int64": 8, "unsigned __int64": 8, "_QWORD": 8}
BASIC_C = {"wchar_t": "unsigned short", "_BYTE": "unsigned char", "_WORD": "unsigned short",
           "_DWORD": "unsigned int", "_QWORD": "unsigned __int64", "BYTE": "unsigned char",
           "WORD": "unsigned short", "DWORD": "unsigned long", "BOOL": "int"}


def type_from_string(ts, size):
    """Turn an IDA type string into (base, suffix) if it is safe and the size agrees, else None."""
    ts = re.sub(r"\b(struct|union|enum|const|volatile)\s+", "", ts).strip()
    m = re.match(r"^([A-Za-z_][A-Za-z0-9_ ]*?)\s*(\*+)?\s*(\[\d+\])*$", ts)
    if not m:
        return None
    base, ptr = m.group(1).strip(), m.group(2) or ""
    dims = [int(x) for x in re.findall(r"\[(\d+)\]", ts)]
    count = 1
    for x in dims:
        count *= x
    if ptr:
        if base in BASIC or base == "void":
            cb = BASIC_C.get(base, base)
        elif base in struct_kind or ident(base) in ENUM_NAMES:
            cb = ident(base)
        else:
            cb = "void"
        esz = 4
        decl = cb + " " + ptr
    elif base in BASIC:
        cb, esz = BASIC_C.get(base, base), BASIC[base]
        decl = cb + " "
    elif base in struct_kind:
        cb, esz = ident(base), size_of[base]
        decl = cb + " "
    elif ident(base) in ENUM_NAMES:
        cb, esz = ident(base), 4
        decl = cb + " "
    else:
        return None
    if esz * count != size or esz == 0:
        return None
    return decl, "".join("[%d]" % x for x in dims), (base if not ptr and base in struct_kind else None)


DT = {0x00000000: ("unsigned char", 1), 0x10000000: ("unsigned short", 2), 0x20000000: ("unsigned int", 4),
      0x30000000: ("unsigned __int64", 8), 0x80000000: ("float", 4), 0x90000000: ("double", 8)}


def type_from_flags(flags, tref, size):
    dt = flags & 0xF0000000
    if dt == 0x60000000 and tref and tref[0] == "struc_id" and tref[1] in struct_kind and size_of[tref[1]]:
        ssz = size_of[tref[1]]
        if size % ssz == 0:
            n = size // ssz
            return ident(tref[1]) + " ", "" if n == 1 else "[%d]" % n, tref[1]
    if dt == 0x20000000 and size == 4 and (flags & 0x00F00000) == 0x00500000:
        return "void *", "", None
    if dt == 0x20000000 and size == 4 and tref and tref[0] == "enum" and ident(tref[1]) in ENUM_NAMES:
        return ident(tref[1]) + " ", "", None
    if dt == 0x50000000:
        return "char ", "[%d]" % size, None
    if dt in DT and size % DT[dt][1] == 0:
        c, esz = DT[dt]
        n = size // esz
        return c + " ", "" if n == 1 else "[%d]" % n, None
    return "unsigned char ", "[%d]" % size, None


out_structs, deps, model = {}, defaultdict(set), {}
for s in struct_kind:
    lines, pos, base, fields = [], 0, None, []
    for off, name, flags, tref, size in sorted(members[s], key=lambda m: m[0]):
        if struct_kind[s]:
            pos = 0
        if size <= 0 or off < pos:
            lines.append("\t// skipped overlapping/empty member %s at 0x%X" % (name, off))
            continue
        if off > pos:
            lines.append("\tunsigned char _pad_%X[0x%X];" % (pos, off - pos))
        ida_t = mtypes.get((s, off))
        conv = type_from_string(ida_t, size) if ida_t else None
        if conv is None:
            conv = type_from_flags(flags, tref, size)
        decl, dims, dep = conv
        if dep:
            deps[s].add(dep)
        if name == "__parent" and off == 0 and dep and not dims and struct_kind[s] == 0:
            base = dep
        else:
            note = []
            bare = re.sub(r"\b(struct|union|enum)\s+", "", ida_t or "").replace(" ", "")
            if ida_t and bare not in (decl + dims).replace(" ", ""):
                note.append("ida: " + ida_t)
            if (s, off) in mcmts:
                note.append(mcmts[(s, off)][:110])
            lines.append("\t%s%s%s;%s" % (decl, ident(name), dims, ("  // " + " | ".join(note)) if note else ""))
            fields.append({"off": off, "size": size, "decl": decl, "name": ident(name), "dims": dims,
                           "note": " | ".join(note),
                           "struct": ident(dep) if dep and not decl.rstrip().endswith("*") else None})
        pos = off + size
    kw = "union" if struct_kind[s] else "struct"
    head = "%s %s%s {" % (kw, ident(s), " : " + ident(base) if base else "")
    body = lines if lines or base else ["\tunsigned char _empty;"]
    if struct_kind[s]:
        body = [l for l in body if "_pad_" not in l]
    out_structs[s] = "\n".join([head] + body + ["};"])
    model[ident(s)] = {"kind": kw, "size": size_of[s], "base": ident(base) if base else None, "fields": fields}
    if size_of[s]:
        out_structs[s] += "\ntypedef char _size_check_%s[sizeof(%s) == 0x%X ? 1 : -1];" % (ident(s), ident(s), size_of[s])

order, seen = [], set()


def visit(s, stack=()):
    if s in seen or s in stack:
        return
    for d in sorted(deps[s]):
        visit(d, stack + (s,))
    seen.add(s)
    order.append(s)


for s in sorted(struct_kind):
    visit(s)

hdr = ["// Generated by tools/gen_symbols.py from ref/SPEED2.idc (yugecin/nfsu2-re). Do not edit by hand.",
       "// Reference layouts: offsets are exact (explicit padding, pack 1). Names are yugecin's.",
       "#ifndef IDA_TYPES_H", "#define IDA_TYPES_H", "", "#pragma pack(push, 1)", ""]
for e, vals in sorted(enums.items()):
    if vals:
        hdr.append("enum %s {" % ident(e))
        hdr += ["\t%s = 0x%X," % (ident(n), v & 0xFFFFFFFF) for n, v in vals]
        hdr.append("};")
    else:
        hdr.append("enum %s { %s__none };" % (ident(e), ident(e)))
hdr.append("")
hdr += ["%s %s;" % ("union" if struct_kind[s] else "struct", ident(s)) for s in sorted(struct_kind)]
hdr.append("")
for s in order:
    hdr += [out_structs[s], ""]
hdr += ["#pragma pack(pop)", "", "#endif"]
import json
json.dump({"structs": model, "enums": {ident(e): [(ident(n), v & 0xFFFFFFFF) for n, v in vals] for e, vals in enums.items()}},
          open(os.path.join(common.CONFIG, "ida_model.json"), "w"), indent=0)
path = os.path.join(common.ROOT, "include", "ida", "ida_types.h")
open(path, "w").write("\n".join(hdr) + "\n")
print("ida_types.h: %d structs/unions, %d enums" % (len(struct_kind), len(enums)))
