// PROFILE: game
// UnloadPCLoadingFNGIfLoaded, 29 bytes
// yugecin's prototype: void __cdecl UnloadPCLoadingFNGIfLoaded();
bool IsFNGLoaded_(const char *fngName);
void sub_558F00(const char *fngName);

// FUNCTION: 0x004A9310
void UnloadPCLoadingFNGIfLoaded()
{
	if (IsFNGLoaded_("PC_Loading.fng"))
		sub_558F00("PC_Loading.fng");
}
