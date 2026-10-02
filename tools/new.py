"""Start a source file for an original function.

  python tools/new.py 52C2F0 ui        creates src/game/ui/0052C2F0_<name>.cpp
  python tools/new.py 7201C2 ealibs --profile lib_o1_frame --lib

The file gets the profile line, yugecin's prototype and notes as comments, and the FUNCTION
annotation. Write the function body, then run tools/check.py on the file.
"""
import argparse, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

ap = argparse.ArgumentParser()
ap.add_argument("addr")
ap.add_argument("area", help="subfolder, e.g. ui, career, cars, world, misc")
ap.add_argument("--profile", default="game")
ap.add_argument("--lib", action="store_true", help="put it under src/lib instead of src/game")
a = ap.parse_args()

addr = int(a.addr, 16)
f = common.functions().get(addr)
if not f:
    sys.exit("%X is not the start of a function in the IDA export" % addr)
name = re.sub(r"[^A-Za-z0-9_]+", "_", f["name"]).strip("_") if f["name"] else ""
fname = "%08X%s.cpp" % (addr, "_" + name if name else "")
path = os.path.join(common.ROOT, "src", "lib" if a.lib else "game", a.area, fname)
if os.path.exists(path):
    sys.exit("already exists: " + path)
lines = ["// PROFILE: " + a.profile, ""]
lines.append("// %s, %d bytes, region %s" % (f["name"] or "sub_%X" % addr, f["size"], f["region"]))
if f["type"]:
    lines.append("// yugecin's prototype: " + f["type"])
if f["comment"]:
    lines.append("// yugecin's note: " + f["comment"])
lines += ["// See: python tools/disasm.py %X" % addr, "", "// FUNCTION: 0x%08X" % addr, ""]
os.makedirs(os.path.dirname(path), exist_ok=True)
open(path, "w").write("\n".join(lines) + "\n")
print(path)
