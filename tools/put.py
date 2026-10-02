"""Write several function source files from one input on stdin (handy when working in batches).

  python tools/put.py <<'EOF'
  === 500F90 career
  #include "game/Career.h"

  // FUNCTION
  int Career::sub_500F90() { return 0; }
  === 4FE140 career --profile game_noeh
  ...
  EOF

Each "=== <address> <area> [--profile name] [--lib]" starts a file, written to
src/game/<area>/<ADDR>_<name>.cpp (or src/lib/...). A line that is just "// FUNCTION" becomes the
annotation for that address. The profile line and yugecin's prototype/notes are added at the top.
Existing files are overwritten.
"""
import os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import common

text = sys.stdin.read()
parts = re.split(r"^=== (.*)$", text, flags=re.M)
written = []
for head, body in zip(parts[1::2], parts[2::2]):
    args = head.split()
    addr, area = int(args[0], 16), args[1]
    profile = args[args.index("--profile") + 1] if "--profile" in args else "game"
    f = common.functions()[addr]
    name = re.sub(r"[^A-Za-z0-9_]+", "_", f["name"]).strip("_") if f["name"] else ""
    path = os.path.join(common.ROOT, "src", "lib" if "--lib" in args else "game", area,
                        "%08X%s.cpp" % (addr, "_" + name if name else ""))
    lines = ["// PROFILE: " + profile]
    lines.append("// %s, %d bytes" % (f["name"] or "sub_%X" % addr, f["size"]))
    if f["type"]:
        lines.append("// yugecin's prototype: " + f["type"])
    if f["comment"]:
        lines.append("// yugecin's note: " + f["comment"])
    body = re.sub(r"^// FUNCTION\s*$", "// FUNCTION: 0x%08X" % addr, body.strip("\n"), flags=re.M)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    open(path, "w").write("\n".join(lines) + "\n" + body + "\n")
    written.append(os.path.relpath(path, common.ROOT))
print("\n".join(written))
