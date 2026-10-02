"""Shared helpers for the nfsu2-decomp tools: paths, the original exe, symbols, regions,
COFF object parsing, compiling with VC7.1 and comparing compiled code against the exe."""
import csv, json, os, re, struct, subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONFIG = os.path.join(ROOT, "config")
BUILD = os.path.join(ROOT, "build")


def _load_json(name):
    with open(os.path.join(CONFIG, name)) as f:
        return json.load(f)


PATHS = _load_json("paths.json")
PROFILES = _load_json("profiles.json")
CC = PATHS["compiler"]
CC_BIN = os.path.join(CC, "Vc7", "bin")


def cc_env():
    env = dict(os.environ)
    env["PATH"] = CC_BIN + ";" + os.path.join(CC, "Common7", "IDE") + ";" + env.get("PATH", "")
    env["INCLUDE"] = os.path.join(CC, "Vc7", "include")
    env["LIB"] = os.path.join(CC, "Vc7", "lib")
    return env


# ---------------------------------------------------------------- original exe

class Exe:
    def __init__(self, path=PATHS["exe"]):
        self.data = open(path, "rb").read()
        d = self.data
        pe = struct.unpack_from("<I", d, 0x3C)[0]
        nsec = struct.unpack_from("<H", d, pe + 6)[0]
        optsz = struct.unpack_from("<H", d, pe + 20)[0]
        self.base = struct.unpack_from("<I", d, pe + 24 + 28)[0]
        self.sections = []
        for i in range(nsec):
            o = pe + 24 + optsz + i * 40
            vsz, va, rsz, rptr = struct.unpack_from("<IIII", d, o + 8)
            self.sections.append((self.base + va, vsz, rptr, rsz))

    def read(self, va, n):
        for sva, vsz, rptr, rsz in self.sections:
            if sva <= va < sva + rsz:
                off = rptr + va - sva
                return self.data[off:off + n]
        return b""


_exe = None


def exe():
    global _exe
    if _exe is None:
        _exe = Exe()
    return _exe


# ---------------------------------------------------------------- symbols and regions

def load_regions():
    with open(os.path.join(CONFIG, "regions.csv")) as f:
        return [(int(r["start"], 16), int(r["end"], 16), r["label"], r["scope"]) for r in csv.DictReader(f)]


REGIONS = load_regions()


def region_of(addr):
    for lo, hi, label, scope in REGIONS:
        if lo <= addr < hi:
            return label
    return "other"


_symbols = None


def symbols():
    """addr -> dict(kind, addr, end, size, region, name, type) from config/symbols.csv."""
    global _symbols
    if _symbols is None:
        _symbols = {}
        path = os.path.join(CONFIG, "symbols.csv")
        if os.path.exists(path):
            with open(path, newline="") as f:
                for r in csv.DictReader(f):
                    a = int(r["addr"], 16)
                    r["addr"] = a
                    r["end"] = int(r["end"], 16) if r["end"] else 0
                    r["size"] = int(r["size"]) if r["size"] else 0
                    _symbols[a] = r
    return _symbols


def functions():
    return {a: s for a, s in symbols().items() if s["kind"] == "func"}


def name_index():
    """Lookup table from a normalized symbol name to its address."""
    idx = {}
    for a, s in symbols().items():
        if s["name"]:
            idx.setdefault(normalize_name(s["name"]), a)
    return idx


def normalize_name(n):
    n = n.strip().lstrip("?").rstrip("?")
    n = re.sub(r"::ctor$", "::__ctor", n)
    n = re.sub(r"::dtor$", "::__dtor", n)
    return n


# ---------------------------------------------------------------- COFF objects

def parse_coff(d):
    """Return (sections, symbols) of a COFF object. symbols: list of dicts."""
    nsec, _, symptr, nsym = struct.unpack_from("<HIII", d, 2)
    secs = []
    for i in range(nsec):
        o = 20 + i * 40
        name = d[o:o + 8].rstrip(b"\0").decode("latin1")
        _, _, rsz, rptr, relptr, _, nrel, _, ch = struct.unpack_from("<IIIIIIHHI", d, o + 8)
        rels = []
        for r in range(nrel):
            va, si, typ = struct.unpack_from("<IIH", d, relptr + r * 10)
            rels.append((va, si, typ))
        secs.append({"name": name, "size": rsz, "ptr": rptr, "relocs": rels, "chars": ch})
    strtab = symptr + nsym * 18
    syms, i = [], 0
    while i < nsym:
        o = symptr + i * 18
        if d[o:o + 4] == b"\0\0\0\0":
            so = strtab + struct.unpack_from("<I", d, o + 4)[0]
            name = d[so:d.index(b"\0", so)].decode("latin1")
        else:
            name = d[o:o + 8].rstrip(b"\0").decode("latin1")
        value, secnum, typ, cls, naux = struct.unpack_from("<IhHBB", d, o + 8)
        syms.append({"index": i, "name": name, "value": value, "section": secnum, "type": typ, "class": cls})
        i += 1 + naux
    return secs, syms


def coff_functions(path):
    """name -> (code bytes, [reloc offsets], [(offset, target symbol name, type)]) for function symbols."""
    d = open(path, "rb").read()
    secs, syms = parse_coff(d)
    byidx = {s["index"]: s for s in syms}
    funcs = [s for s in syms if s["section"] > 0 and s["type"] == 0x20
             and not s["name"].startswith(("__ehhandler$", "__unwindfunclet$", "__catch$"))]
    out = {}
    for s in funcs:
        sec = secs[s["section"] - 1]
        later = sorted(x["value"] for x in funcs if x["section"] == s["section"] and x["value"] > s["value"])
        end = later[0] if later else sec["size"]
        code = d[sec["ptr"] + s["value"]:sec["ptr"] + end]
        rel = [(va - s["value"], byidx.get(si, {}).get("name", "?"), typ)
               for va, si, typ in sec["relocs"] if s["value"] <= va < end]
        out[s["name"]] = (code, rel)
    return out


def coff_literals(path):
    """name -> bytes for string literals (??_C@) and floating-point constants (__real@) defined in obj."""
    d = open(path, "rb").read()
    secs, syms = parse_coff(d)
    out = {}
    for s in syms:
        if s["section"] > 0 and s["name"].startswith(("??_C@", "__real@")):
            sec = secs[s["section"] - 1]
            out[s["name"]] = d[sec["ptr"] + s["value"]:sec["ptr"] + sec["size"]]
    return out


def literal_mismatches(addr, code, rel, literals):
    """For a byte-matched function, check that the literals it references have the original contents."""
    orig = exe().read(addr, len(code))
    bad = []
    for off, name, typ in rel:
        if typ != 0x06 or name not in literals:
            continue
        target = struct.unpack_from("<I", orig, off)[0] - struct.unpack_from("<i", code, off)[0]
        ours = literals[name]
        if exe().read(target, len(ours)) != ours:
            theirs = exe().read(target, 64)
            theirs = theirs.split(b"\0")[0] if name.startswith("??_C@") else theirs[:len(ours)]
            bad.append("%s: ours %r, original %r" % (name[:24], ours.rstrip(b"\0")[:40], theirs[:40]))
    return bad


# ---------------------------------------------------------------- compile and compare

def compile_cpp(src, obj, profile="game", extra=()):
    flags = PROFILES[profile].split()
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    cmd = [os.path.join(CC_BIN, "cl.exe"), "/nologo", "/c", "/TP", *flags,
           "/I" + os.path.join(ROOT, "include"), *extra, "/Fo" + obj, src]
    p = subprocess.run(cmd, capture_output=True, text=True, env=cc_env())
    return p.returncode == 0, (p.stdout + p.stderr).strip()


def compare(addr, code, rel, size=None):
    """Compare compiled code against the original function at addr, masking relocated fields.
    Returns (matched, similarity 0..1, original bytes)."""
    if size is None:
        f = functions().get(addr)
        size = (f["end"] - addr) if f else len(code)
    if len(code) > size and any(off >= size for off, _, _ in rel):
        # a switch's jump table placed after the code: IDA's function end stops before it
        size = len(code)
    theirs = bytearray(exe().read(addr, size))
    mine = bytearray(code)
    while mine and mine[-1] in (0xCC, 0x90) and len(mine) > len(theirs):
        mine.pop()
    for off, _, _ in rel:
        for k in range(4):
            if off + k < len(mine):
                mine[off + k] = 0
            if off + k < len(theirs):
                theirs[off + k] = 0
    if mine == theirs:
        return True, 1.0, bytes(theirs)
    original = exe().read(addr, size)
    return False, similarity(code, rel, original), bytes(theirs)


def disasm(code, addr=0):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(code, addr))


def with_reloc_sentinels(code, rel):
    """Fill relocated fields with an address-like value so they normalize like real addresses."""
    b = bytearray(code)
    for off, _, _ in rel:
        b[off:off + 4] = struct.pack("<I", 0x00800000)
    return bytes(b)


def normalized(code):
    """[(instruction, text)] where addresses and calls/jumps leaving the function become X."""
    out = []
    for i in disasm(code):
        s = i.mnemonic + " " + i.op_str
        if i.mnemonic == "call" or i.mnemonic.startswith("j"):
            m = re.fullmatch(r"0x([0-9a-f]+)", i.op_str)
            if m and not 0 <= int(m.group(1), 16) < len(code):
                s = i.mnemonic + " X"
        s = re.sub(r"0x[0-9a-f]+", lambda m: "X" if int(m.group(), 16) >= 0x400000 else m.group(), s)
        out.append((i, s))
    return out


def similarity(code, rel, original):
    import difflib
    x = [s for _, s in normalized(with_reloc_sentinels(code, rel))]
    y = [s for _, s in normalized(original)]
    if not x and not y:
        return 1.0
    return difflib.SequenceMatcher(None, x, y, autojunk=False).ratio()
