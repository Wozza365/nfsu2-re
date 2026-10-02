// PROFILE: game
// SomeAllocWrapper, 23 bytes
// yugecin's prototype: int __cdecl SomeAllocWrapper(int size, int);
int SomeAlloc_(int size, int somestring, int a3, int a4);

// FUNCTION: 0x00440820
int SomeAllocWrapper(int size, int a2)
{
	return SomeAlloc_(size, 0, 0, a2);
}
