# Working on this repo

A matching decompilation of Need for Speed: Underground 2 (PC, `SPEED2.EXE` v1.2), aimed at ports
(web first, then maybe PS Vita). Start with `README.md` (workflow), then `docs/status.md` (where
things stand, decisions, what to do next), `docs/notes.md` (everything learned about matching) and
`docs/worklist.md` (functions not started yet).

## Rules

- Never commit or publish the game, its files, `SPEED2.EXE`, or the Microsoft compiler. This repo
  holds only our own source, tools, notes, and yugecin's public IDA export (`ref/`).
- `yugecin-nfsu2-re/` is the original reverse-engineering project this started from (yugecin's
  nfsu2-re, via the Wozza365 fork, at commit 192090c). Treat it as reference; the decomp lives at the
  root.
- Matching is byte-exact; `EQUIVALENT` is an escape hatch for functions reviewed as identical in
  behaviour that can't be matched. Use it sparingly.
- Networking (the EA online library) is to be stubbed, not decompiled. D3DX and the C runtime get
  replaced.

## What needs the local machine

The compiler (Visual C++ .NET 2003, cl 13.10.3077) and the game exe are only on the owner's PC
(paths in `config/paths.json`). Without them, `tools/check.py`, `tools/disasm.py` and
`tools/build_loader.py` can't run. In a cloud session you can still read and write source, headers
and docs, and plan work; matching has to be checked on the PC.

## Workflow habits that helped

- Use `python tools/check.py --try <dir or file> [--diff ADDR]` for experiments; it saves nothing.
- Read a function with `python tools/disasm.py ADDR`; look up fields with `python tools/layout.py`.
- Shell commands: use absolute paths. Delete nothing with variable paths.
- When a function won't match, the cause is usually source shape (see `docs/notes.md`) or which
  functions share a compilation unit (jumbo files, `src/game/z*.cpp`).
