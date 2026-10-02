// PROFILE: game
// CreateChyronIGFNGObject, 18 bytes
// yugecin's prototype: void __cdecl CreateChyronIGFNGObject();
// yugecin's note: and put it in {836498.40}
int SomeAllocWrapper(int size, int a2);
extern int g_8364D8;

// FUNCTION: 0x004AC920
void CreateChyronIGFNGObject()
{
	g_8364D8 = SomeAllocWrapper(0x60, 0);
}
