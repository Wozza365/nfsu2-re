// PROFILE: game
// LoadGarageMainFNGIfNotLoadedAlready, 39 bytes
// yugecin's prototype: void __cdecl LoadGarageMainFNGIfNotLoadedAlready();
bool IsFNGLoaded_(const char *fngName);
void sub_555F50(int a1, const char *fngName, int a3, int a4, int a5);

// FUNCTION: 0x004A78B0
void LoadGarageMainFNGIfNotLoadedAlready()
{
	if (!IsFNGLoaded_("GarageMain.fng"))
		sub_555F50(0, "GarageMain.fng", 0, 0, 0);
}
