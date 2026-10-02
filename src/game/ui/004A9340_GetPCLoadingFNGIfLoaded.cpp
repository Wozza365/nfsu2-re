// PROFILE: game
// GetPCLoadingFNGIfLoaded, 23 bytes
// yugecin's prototype: char *__cdecl GetPCLoadingFNGIfLoaded();
bool IsFNGLoaded_(const char *fngName);

// FUNCTION: 0x004A9340
const char *GetPCLoadingFNGIfLoaded()
{
	return IsFNGLoaded_("PC_Loading.fng") ? "PC_Loading.fng" : 0;
}
