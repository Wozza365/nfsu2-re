"""Disassemble original functions with names, prototypes, strings and float constants filled in.

  python tools/disasm.py 52C2F0 4615A0          by address (several at once is fine)
  python tools/disasm.py UILabel::SetStringToDialogText
  python tools/disasm.py 52C2F0 --callers       also list known direct callers
"""
import os, re, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common


def label(a):
    s = common.symbols().get(a)
    if s and s["name"]:
        return s["name"]
    f = common.functions().get(a)
    return "sub_%X" % a if f else None


def peek(a):
    """Describe what lives at a data address: a string, a float, or a named item."""
    raw = common.exe().read(a, 64)
    if not raw:
        return None
    m = re.match(rb"([\x20-\x7e]{4,})\x00", raw)
    if m:
        return '"%s"' % m.group(1).decode()[:48]
    v = struct.unpack("<f", raw[:4])[0]
    if raw[:4] != b"\0\0\0\0" and 1e-6 < abs(v) < 1e9:
        return "float %g" % v
    return None


def dis(addr):
    f = common.functions()[addr]
    print("%X..%X  size %d  region %s  %s" % (addr, f["end"], f["size"], f["region"], f["name"]))
    if f["type"]:
        print("type: " + f["type"])
    if f["comment"]:
        print("note: " + f["comment"])
    for i in common.disasm(common.exe().read(addr, f["size"]), addr):
        notes = []
        for m in re.findall(r"0x[0-9a-f]{6,8}", i.op_str):
            a = int(m, 16)
            n = label(a)
            if n and not (addr <= a < f["end"]):
                notes.append(n)
            elif not n and not (i.mnemonic == "call" or i.mnemonic.startswith("j")):
                p = peek(a)
                if p:
                    notes.append(p)
        print("  %X: %-30s%s" % (i.address, i.mnemonic + " " + i.op_str, ("  ; " + ", ".join(notes)) if notes else ""))


def callers(addr):
    data = common.exe()
    out = []
    for a, f in common.functions().items():
        code = data.read(a, f["size"])
        for k in range(len(code) - 4):
            if code[k] == 0xE8 and a + k + 5 + struct.unpack_from("<i", code, k + 1)[0] == addr:
                out.append(a)
                break
    print("callers: " + (", ".join("%X %s" % (c, label(c) or "") for c in sorted(out)) or "none found"))


if __name__ == "__main__":
    idx = {s["name"]: a for a, s in common.functions().items() if s["name"]}
    for want in [x for x in sys.argv[1:] if not x.startswith("--")]:
        addr = idx[want] if want in idx else int(want, 16)
        dis(addr)
        if "--callers" in sys.argv:
            callers(addr)
        print()
