// Runtime loader for nfsu2-decomp, built by tools/build_loader.py into nfsu2decomp.asi.
//
// The Ultimate ASI Loader (dinput8.dll in the game folder) loads this from scripts\ before the game
// runs. For every recompiled function in the generated hook table it checks that the whole original
// function is unchanged, then writes a jmp from the original function to ours. It is installed as
// zz_nfsu2decomp.asi so it loads after other mods: a function another mod has patched is left alone.
//
// nfsu2decomp.ini (next to the .asi, optional):
//   [loader]
//   enabled=1                 ; 0 turns every hook off
//   disable=4615A0,504400     ; hex addresses to leave alone, for bisecting problems
// Every run writes nfsu2decomp.log next to the .asi.
#include <stdio.h>
#include <string.h>

extern "C" {
__declspec(dllimport) int __stdcall VirtualProtect(void *addr, unsigned long size, unsigned long prot, unsigned long *old);
__declspec(dllimport) int __stdcall FlushInstructionCache(void *process, const void *addr, unsigned long size);
__declspec(dllimport) void *__stdcall GetCurrentProcess();
__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *module, char *out, unsigned long size);
__declspec(dllimport) unsigned long __stdcall GetPrivateProfileStringA(const char *section, const char *key,
	const char *def, char *out, unsigned long size, const char *file);
}

struct Hook {
	unsigned int original;      // address in SPEED2.EXE
	void *replacement;          // recompiled function in this DLL
	unsigned int size;          // size of the original function
	unsigned char expect[8];    // first bytes of the original function when the table was built
	const char *name;
	unsigned int crc;           // CRC-32 of the whole original function
};
extern "C" Hook nfsu2_hooks[];

static unsigned int crc32(const unsigned char *p, unsigned int n)
{
	unsigned int c = 0xFFFFFFFF;
	while (n--) {
		c ^= *p++;
		for (int k = 0; k < 8; k++)
			c = (c >> 1) ^ (0xEDB88320 & (0 - (c & 1)));
	}
	return ~c;
}

static void path_next_to_dll(void *module, const char *file, char *out, unsigned long n)
{
	GetModuleFileNameA(module, out, n);
	char *slash = strrchr(out, '\\');
	strcpy(slash ? slash + 1 : out, file);
}

static int in_list(const char *list, unsigned int addr)
{
	char hex[16];
	sprintf(hex, "%X", addr);
	size_t n = strlen(hex);
	for (const char *p = list; (p = strstr(p, hex)) != 0; p += n) {
		int starts = p == list || p[-1] == ',' || p[-1] == ' ';
		int ends = p[n] == 0 || p[n] == ',' || p[n] == ' ';
		if (starts && ends)
			return 1;
	}
	return 0;
}

static void install(void *module)
{
	char ini[260], logpath[260], enabled[8], disabled[4096];
	path_next_to_dll(module, "nfsu2decomp.ini", ini, sizeof(ini));
	path_next_to_dll(module, "nfsu2decomp.log", logpath, sizeof(logpath));
	FILE *log = fopen(logpath, "w");
	GetPrivateProfileStringA("loader", "enabled", "1", enabled, sizeof(enabled), ini);
	GetPrivateProfileStringA("loader", "disable", "", disabled, sizeof(disabled), ini);
	if (enabled[0] == '0') {
		if (log) { fprintf(log, "loader disabled by nfsu2decomp.ini\n"); fclose(log); }
		return;
	}
	int patched = 0, skipped = 0;
	for (Hook *h = nfsu2_hooks; h->original; h++) {
		unsigned char *at = (unsigned char *) h->original;
		const char *why = 0;
		if (in_list(disabled, h->original))
			why = "disabled in ini";
		else if (memcmp(at, h->expect, h->size < 8 ? h->size : 8) != 0 || crc32(at, h->size) != h->crc)
			why = "original bytes differ (different exe, or another mod patched it)";
		if (why) {
			if (log) fprintf(log, "skip  %06X %s: %s\n", h->original, h->name, why);
			skipped++;
			continue;
		}
		unsigned long old;
		VirtualProtect(at, 5, 0x40 /* PAGE_EXECUTE_READWRITE */, &old);
		at[0] = 0xE9;
		*(int *) (at + 1) = (int) h->replacement - (int) (at + 5);
		VirtualProtect(at, 5, old, &old);
		FlushInstructionCache(GetCurrentProcess(), at, 5);
		if (log) fprintf(log, "hook  %06X -> %08X %s\n", h->original, (unsigned int) h->replacement, h->name);
		patched++;
	}
	if (log) {
		fprintf(log, "%d hooked, %d skipped\n", patched, skipped);
		fclose(log);
	}
}

extern "C" int __stdcall DllMain(void *module, unsigned long reason, void *)
{
	if (reason == 1 /* DLL_PROCESS_ATTACH */)
		install(module);
	return 1;
}
