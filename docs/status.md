# Status and decisions

Where the project stands (2 October 2026) and what was decided along the way. `docs/notes.md` has
the technical findings; `reports/progress.md` has the numbers.

## Goal

A full decompilation of NFS Underground 2, for ports: a web build first, then possibly PS Vita (a
decomp also allows scaling assets down for weaker hardware). Recent decomps (Call of Duty, Halo)
and the Most Wanted decomp (`dbalatoni13/nfsmw`, CC0) show it can be done; Most Wanted shares
EA's engine code (bWare, the z*.cpp jumbo layout) with this game.

## Inputs

- `SPEED2.EXE` v1.2, MD5 `6445adbf4e8d64be51e96a69bba168a4` (a modified copy, timestamp 1987,
  two extra sections; code unencrypted).
- yugecin's IDA export (`ref/SPEED2.idc`, public on the upstream `idc` branch): 18,444 functions,
  3,174 named, 507 structs. It lines up with this exe. `tools/gen_symbols.py` turns it into
  `config/symbols.csv`, `config/ida_model.json` and `include/ida/ida_types.h`.
- yugecin's site: https://yugecin.github.io/nfsu2-re/ (docs for the original project).
- The Most Wanted decomp, for EA's shared headers (`include/bWare/` came from there).

## Toolchain (verified)

- Game code: Visual C++ 7.1 build 3077 (Visual Studio .NET 2003). Extracted from a VS .NET 2003
  Professional disc image; link.exe and mspdb71.dll are byte-identical to Microsoft's symbol server
  copies. The free Visual C++ Toolkit 2003 (build 3052) gives the same output on everything tried.
- The exe's C runtime and C++ library are VC 7.0 (build 9466) objects, linked with the 7.0 linker;
  they get replaced, not matched.
- Flags: `/O2 /GR- /Gy /GX` (profiles in `config/profiles.json`). Some library C code is `/O1`.
  `/G6`, `/G7`, `/Os`, `/O1`, `/Ob1` all make game code worse.

## Phases

- Phase 0 (done): toolchain identification, tools (`tools/`), the runtime loader, a pilot of 18
  functions.
- Phase 1 (in progress): matching the Career area, smallest functions first, to learn EA's source
  shapes. Batch 1 (functions of 64 bytes or less) and most of batch 2 (65-128 bytes) are done.
- Later: reconstruct EA's jumbo files by address range, then bigger functions and other areas, then
  replace the libraries (D3DX, C runtime), stub networking, and start porting.

## Numbers so far

- 215 functions match byte for byte (212 in game code, 0.46% of game-code bytes), 1 equivalent,
  18 near misses kept as nonmatching with a reason at the top of each file.
- 52 of those came from a helper agent working on small loader/pool/utility functions in parallel
  (`src/game/bin`, `pool`, `misc`, `text`, `ui`).
- The runtime loader (`tools/build_loader.py`) hooks 210 matched functions into the real game and
  verifies each is byte-identical and reaches the same targets. It has never been run in the game:
  an in-game smoke test is still owed (copy `build/loader/nfsu2decomp.asi` to
  `<game>/scripts/zz_nfsu2decomp.asi` and play career menus and a race).

## The big finding: jumbo files

EA compiled the game as jumbo files (one .cpp `#include`ing many), like Most Wanted's
`SourceLists/z*.cpp`. That is why some functions only match next to others: inlining of plain
functions, register and global side-effect knowledge of already-compiled callees, and custom
calling conventions for static helpers all depend on sharing a compilation unit. `check.py`
compiles jumbo files as one unit; `src/game/zCareer.cpp` and `src/game/zSms.cpp` are the first.
The address order in the exe follows the order inside each jumbo file, so address ranges are the
best guide to rebuilding them.

## Open questions

- About half the game's `[esp]` operands use an explicit zero displacement (`[esp+0]`); our
  compiler always uses the short form (5005E0 is EQUIVALENT because of it).
- The order of the three setup instructions before `rep stosd` (512EB0, 516A60).
- Small structs copied through a stack temporary with `rep movsd` (4133D0, 500EA0).
- A constructor that stores the same zeros twice (5F73D0).
- 514340 is inlined into its only caller by our compiler but not in the game.
- The region 0x6D8000-0x6F0000 isn't identified; EA's audio library (AEMS) isn't located.
- `config/regions.csv` puts 0x638000+ in D3DX, but 0x639CE0 is a MenuCarInstance method, so the
  boundary is probably a little later.

## Decisions

- Matching: byte-exact, with the EQUIVALENT escape hatch.
- Networking can be stubbed.
- Never commit game files, the exe, or the compiler.
- The repo is private (`Wozza365/nfsu2-re2`); the original project is kept under
  `yugecin-nfsu2-re/`.

## Next steps

1. Smoke-test the loader in the game.
2. Finish batch 2: about 25 Career-area functions of 100-128 bytes are left (see
   `config/symbols.csv` for Career, CareerStage, CarCollection, SmsMessageList methods).
3. Grow the jumbo files by address range: move the matched functions near 0x500000-0x541000
   into `zCareer.cpp`, the SMS ones into `zSms.cpp`, and recheck.
4. Work the open questions above; each one affects many functions.
5. More helper agents can take whole areas in parallel, if each writes only its own files and uses
   `check.py --try` (shared results and headers are the collision points).
