# Notes

What the pilot and Phase 0 established (October 2026).

## The exe

- `SPEED2.EXE` v1.2, 4,800,512 bytes, MD5 `6445adbf4e8d64be51e96a69bba168a4`. A modified copy: the
  timestamp reads 1987 and there are two extra unnamed sections. The code is plain and unencrypted.
- yugecin's IDA export lines up with this exe: about 93-98% of sampled function boundaries and
  strings agree. 18,444 functions; 3,174 named; 507 structs; 49 enums; ~46k comments.
- Regions (`config/regions.csv`, approximate, from alignment, names and strings):

| Range | What | Plan |
|---|---|---|
| 0x401000-0x638000 | EA game code, ~10,250 functions | decompile |
| 0x638000-0x6D8000 | Microsoft D3DX (shader assembler, effect compiler strings) | replace |
| 0x6D8000-0x6F0000 | aligned C++, not identified yet | decompile? |
| 0x6F0000-0x730000 | EA RealCore 6.23 file system; On2 VP6 6.1.0.5 (~0x70CC77); likely zlib 1.1.4 and libjpeg | split |
| 0x730000-0x75BBF0 | EA online/socket library | stub |
| 0x75BBF0-0x771303 | import thunks + Microsoft C runtime (entry 0x75BCC7) | replace |
| 0x771303-0x77A5F6 | compiler-generated exception handlers and unwind funclets | automatic |
| 0x77A5F6-0x783000 | dynamic initializers / atexit stubs for globals | automatic |

EA's audio engine (AEMS) is referenced but not located yet.

## Compiler

- The Rich header records the build tools. Game code: VC 7.1 build 3077 (Visual Studio .NET 2003),
  ~251 C++ and 87 C objects. Microsoft C runtime and C++ library: VC 7.0 build 9466, linked with the
  7.0 linker. D3DX: 13.10.4035 (121 objects).
- The runtime evidence: the exe's `WinMainCRTStartup` and EH vector helpers differ from the 7.1
  runtime; `atexit` and the frame handler thunk are identical.
- The Visual C++ Toolkit 2003 (13.10.3052) gave identical output to 3077 on everything tried.
- Flags: game code `/O2 /GR- /Gy /GX` (no RTTI; C++ exceptions on, the exe has ~2,300 EH funclets).
  Some library C code needs `/O1`, and some `/O1 /Oy-`. `/G6`/`/G7` break matches; leave them off.

## Matching lessons so far

- Source shape matters even when the logic is right:
  - `len + 1` written at each use matched where a cached `len = x + 1` did not
  - a field zeroed by a member's own constructor fixed store order
  - a `do/while` search loop stopped the unrolling a `for` loop got
- EA's shared code headers transfer from the Most Wanted decomp. `bTList`'s casts give the null-checked
  `lea eax,[x-0x10]` pattern; `bClamp(i, 0, n)` gives the branch-free `setle/dec/and` clamp.
- yugecin's prototypes are usually right about parameters but sometimes wrong about return types:
  `FontData::MeasureWidth` returns a float.
- `check.py` masks address fields, so wrong string literals would slip through. It now compares
  literal contents too: the pilot had invented `"UI_DecalsOverlay"` for `"UI_DecalsOverlayInvis.fng"`.

## Phase 1 lessons (career batch)

- yugecin's prototypes often say `int` where the function only sets `al`: the real type is `bool`
  or `unsigned char`. Something that only stores and returns leftover `eax` is `void`.
- `bool` results: `return a && b;` and `return p != 0;` compute a full int (`mov eax,1` /
  `neg/sbb/neg`). The game usually has `mov al,1` / `setne al`: write `if (...) return true;
  return false;`, `p ? true : false`, or rely on an implicit pointer-to-bool conversion. Which
  branch comes first follows the source: `if (!p) return false; return true;` vs the reverse.
- Success-first is common: `if (p) return p->x; return -1;` lays out differently from the inverse.
- Comparison operand order is preserved: `hash == a[i].hash` and `a[i].hash == hash` differ.
- A value read into a named local first can change which register is used (`TunedCar::GetCarIndex`).
- `float / int` compiles to `fild` + `fdivr`; the game's `fld` + `fidiv` comes from a double divide.
- Small functions get inlined into their siblings (`HasFreeEntryInTunedCars` contains
  `GetFreeTunedCarSlot`), so they were in the same source file. For now the caller's file
  `#include`s the sibling's; eventually files should follow EA's original source files.
- Fields yugecin split for IDA (`Career::stage0..7`) are arrays in the code (`stages[8]`), with an
  inline `GetStage(i)` that returns 0 out of range (and callers dereference it anyway).
- Classes with vtables need real `virtual` declarations in the header: constructors and
  destructors then store the vtable themselves. Identical vtables and functions were folded by
  the linker (/OPT:ICF): `StockCar`, `SponsorCar` and `TunedCar` share one destructor.
- Open question: about half the game's `[esp]` operands are encoded with an explicit zero
  displacement (`[esp+0]`, one byte longer); VC 7.1 3077 always used the short form here.
- Methods that callers inline (`SmsMessageList::GetAtIndex`, `CarCollection::FindStockCar`,
  `GetFreeTunedCarSlot`, `Career::FindCareer7B00WithHash0`) were inline in their class headers; the
  game also has one out-of-line copy of each. Define them in the header and give the out-of-line
  copy a file that takes the method's address (see `src/game/sms/005014A0_*.cpp`).
- The compiler knows what a callee in the same source file does with registers: `Career::5410E0`
  keeps using `ecx` after calling `sub_512F10`, and only matches with `sub_512F10` defined in the
  same file. `static` helpers in the same file get custom calling conventions (arguments in `eax` or
  `edx`). So callers of those need their callees decompiled into the same file first. Deferred for
  that reason: `Career7148::5007A0` (helper `5002E0` takes `eax`), `Career::5143C0` (helper `514340`
  takes `edx`).
- Some functions were built with frame pointers (`push ebp / mov ebp, esp`) while their neighbours
  weren't: `#pragma optimize("y", off)` around just that function reproduces it.
- Open: a 24-byte copy the game does with `rep movsd` (ecx=6) comes out as six moves here, from both
  `memcpy` and struct assignment (`Career::CopyIntoFirstAvailableField0`).
- Open: a constructor that stores the same zeros twice (`CareerD24_54_30_0_10C`); our compiler drops
  the repeat as redundant.
- For later phases: these all point the same way. To match well at scale, the source should be
  grouped into files the way EA's was, because inlining, register knowledge and custom calling
  conventions all depend on what shares a file.

## Loader

- The linker refuses calls to absolute symbols (LNK2016), so calls go through `jmp [cell]` stubs;
  data references are absolute symbols with no base relocation.
- Every relocated field of a matched function sits at the same offset as in the original, so the
  real targets (callees, globals, vtables, `operator new` = 0x575620) are read from the exe.
  `operator delete` (0x575630) is in `config/externs.csv`.
- Our objects' vtable references are pointed at the game's vtables; our own copies are dropped. The
  linker ignores `LNK_REMOVE` on COMDATs and resolves every undefined symbol in an object even if
  unused, so unreachable COMDATs lose their relocations and orphaned externals become local.
- Not hookable yet: objects that define global data (it must stay the game's), functions under 5
  bytes, and non-matching functions. `EQUIVALENT` ones can be included with `--equivalent`, but the
  byte-for-byte proof doesn't cover them.

## Phase 1 batch 2: jumbo files

- EA built the game as jumbo ("unity") files: the Most Wanted decomp's `SourceLists/z*.cpp` each
  `#include` dozens of .cpp files. Everything in one jumbo file is one compilation unit, so:
  - plain functions get inlined into later functions in the same unit (`/O2` = `/Ob2`), without any
    `inline` keyword: `Career::FindCareer7B00WithHash0` (5003B0) is a normal function, inlined into
    500460, 500B80, 501150, 512F10 and 528500;
  - the compiler remembers what registers and globals an already-compiled function touches:
    512FF0 keeps `this` in ecx across calls to 5003B0 and 512F10; 5130A0 and 513490 keep a global
    count in a register across calls to 500B80; 529BD0 does the same across 514CB0 (but not across
    SendMessage);
  - `static` helpers get custom calling conventions (5002E0 takes its argument in eax).
- `check.py` supports this: a .cpp that `#include`s other .cpp files is compiled as one unit and
  results are reported per included file. `src/game/zCareer.cpp` and `src/game/zSms.cpp` are the
  first two (names are ours). Files are included in exe address order.
- The earlier "inline in the header plus an out-of-line copy" trick works too, but a jumbo file is the
  real structure. Over time, functions should move into jumbo files by address range.
- Static functions can't be hooked by the loader (the hook table can't name them): mark them `NOHOOK`.
  Their callers use our byte-identical copy.
- More source shapes:
  - `return x ? true : false` gives `setne al`; a plain `return x != 1` from a bool function gives
    `xor ecx / setne cl / mov al, cl`. Both occur in the game.
  - An inline `bool` helper with an early `if (!p) return false;` keeps the `setne al / test al, al`
    pair the game has (527890).
  - `if (A || r == -1) return 0; return r;` and `if (b) { if (cost != -1) return cost; } return 0;`
    keep a branch where `r == -1 ? 0 : r` becomes branch-free.
  - Named locals change register choice and evaluation order (500AB0, 54C9D0, 5135A0, 5007A0).
  - An inline `HashIs(race->hash, "NAME")` helper loads the hash before calling cshash (513430).
  - `for (i = 0; i != 8; i++)` gives `jne` (5111F0). Nested loops give the game's unroll-by-row
    (500820, 500910, 500400); a do/while keeps a 10-entry loop from unrolling.
  - Switches: list the cases that go to the default code too, or the jump table range comes out
    different (503D50). check.py now compares jump tables placed after the code.
  - Arrays of a type with a constructor are built with the game's `vector constructor iterator`
    (401650) only if that constructor is out of line (`ZeroedU32`, 401810).
- Still open:
  - the order of the three setup instructions before `rep stosd` (512EB0, 516A60);
  - a small struct copied through a stack temporary with `rep movsd` (4133D0, like 500EA0);
  - 514340 being inlined into its only caller here but not in the game.
