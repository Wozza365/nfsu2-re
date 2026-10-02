// PROFILE: game
// CreateLoadingTipsFNGObject, 18 bytes
// yugecin's prototype: void __cdecl CreateLoadingTipsFNGObject();
// yugecin's note: and put it in {836480}
int SomeAllocWrapper(int size, int a2);
extern int loadingTipsFNGObject;

// FUNCTION: 0x004A83F0
void CreateLoadingTipsFNGObject()
{
	loadingTipsFNGObject = SomeAllocWrapper(0x5C, 0);
}
