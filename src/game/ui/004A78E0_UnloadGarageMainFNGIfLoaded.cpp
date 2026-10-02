// PROFILE: game
// UnloadGarageMainFNGIfLoaded, 29 bytes
// yugecin's prototype: void __cdecl UnloadGarageMainFNGIfLoaded();
bool IsFNGLoaded_(const char *fngName);
void RemoveFNGFromUIObject(const char *fngName);

// FUNCTION: 0x004A78E0
void UnloadGarageMainFNGIfLoaded()
{
	if (IsFNGLoaded_("GarageMain.fng"))
		RemoveFNGFromUIObject("GarageMain.fng");
}
