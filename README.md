# nfsu2-decomp

A matching decompilation of Need for Speed: Underground 2 (PC, `SPEED2.EXE` v1.2), aiming at ports
(web first, then Vita). Functions are rewritten in C++ and compiled with the game's own compiler
until they produce the original bytes. A runtime loader swaps finished functions into the real game,
so the game stays playable while the decompilation is incomplete.

Current numbers: [reports/progress.md](reports/progress.md). Background and findings: [docs/notes.md](docs/notes.md).

This folder holds no game data and no Microsoft software. Never add `SPEED2.EXE`, game files or the
compiler here, and never publish them.

## Setup

- The game installed; its path and the exe's MD5 are in `config/paths.json`.
- Visual C++ .NET 2003 (cl 13.10.3077), extracted to the folder named in `config/paths.json`
  (`Vc7\bin`, `Vc7\include`, `Vc7\lib`, plus `Common7\IDE` with mspdb71/msvcr71/msvcp71).
- Python 3 with `capstone` (`pip install capstone`).
- `python tools/gen_symbols.py` once, to build `config/symbols.csv` and `include/ida/ida_types.h`
  from yugecin's IDA export in `ref/`.

## Working on a function

```
python tools/new.py 52CEF0 ui          # start src/game/ui/0052CEF0_GetFNGInfoByName.cpp
python tools/disasm.py 52CEF0          # the original, with names, strings and constants
python tools/check.py src/game/ui/0052CEF0_GetFNGInfoByName.cpp
python tools/check.py --diff 52CEF0    # side by side with the original, if it doesn't match
python tools/check.py                  # everything; rewrites reports/progress.md
python tools/check.py --try some/dir   # compare variants without touching the saved results
python tools/check.py --try f.cpp --diff 52CEF0   # ...and show the diff for one address
python tools/layout.py Career 7138     # which field is at an offset (walks nested structs)
python tools/gen_class.py Career       # generate include/game/Career.h from the IDA data
python tools/put.py < batch.txt        # write several function files at once (see the script)
python tools/build_loader.py           # build and verify build/loader/nfsu2decomp.asi
python tools/build_loader.py --install # also copy it to <game>\scripts\zz_nfsu2decomp.asi
```

## Conventions

- One function per file, named `<address>_<name>.cpp`, under `src/game/<area>/` or
  `src/lib/<library>/`. Functions that only match in the same compilation unit as others are
  `#include`d by a jumbo file (`src/game/z*.cpp`), the way EA built the game; see docs/notes.md.
- `// PROFILE: <name>` once per file picks the compiler flags from `config/profiles.json`
  (`game` for game code; library code uses others).
- `// FUNCTION: 0x<address>` directly above each function. Options on the same line:
  `SYMBOL=<mangled>` when the name can't be worked out, `EQUIVALENT`, `NOHOOK`.
- Status comes from `check.py`. **match** means identical bytes (addresses masked) and identical
  string and float literals. **nonmatching** functions say why in a comment at the top of the file.
  **EQUIVALENT** is for functions reviewed as behaving the same but impossible to match exactly;
  use it sparingly.
- Class headers live in `include/game/`. `tools/gen_class.py` writes a first version from the IDA
  data (layout plus yugecin's methods, size and offset checked at compile time); after that they are
  edited by hand: fixing return types, adding `virtual`, turning split fields into arrays, making
  methods inline when the game inlines them.
- `include/ida/ida_types.h` is generated reference (507 structs, exact offsets; names are
  yugecin's). Hand-written shared headers go in `include/`; EA's own headers from the
  Most Wanted decomp (CC0) are in `include/bWare/`. Stand-in types inside a source file are fine
  until a real header exists.
- Unnamed callees and globals are written `sub_XXXXXX` / `g_XXXXXX`, so the address stays visible.

## The runtime loader

`build_loader.py` links every matched function into `nfsu2decomp.asi`. The Ultimate ASI Loader
already in the game folder loads it from `scripts\`; it is installed as `zz_nfsu2decomp.asi` so it
loads after other mods. Before patching, it checks a CRC of each whole original function, so a
different exe or a function another mod has patched is skipped, not overwritten.
`nfsu2decomp.ini` next to the .asi can turn everything off (`[loader] enabled=0`), or switch off
single functions (`disable=4615A0,504400`). Every run writes `nfsu2decomp.log`.

Game addresses are read from the original bytes of matched functions, so calls, globals and
vtables point at the game's own. After linking, the build re-reads the DLL and checks that each
hooked function is byte-identical to the original and reaches the same targets.
