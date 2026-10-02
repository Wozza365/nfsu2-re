// PROFILE: game
// NONMATCHING: instructions identical, but the original encodes [esp] with an explicit zero displacement ([esp+0]), 2 bytes longer (open question in docs/notes.md).
// ??perfcountertime, 37 bytes
union _LARGE_INTEGER { struct { unsigned int LowPart; int HighPart; } u; __int64 QuadPart; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(_LARGE_INTEGER *count);
extern int g_8284E4;

// FUNCTION: 0x0043BDF0
int perfcountertime()
{
	_LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (int)(t.QuadPart >> g_8284E4);
}
