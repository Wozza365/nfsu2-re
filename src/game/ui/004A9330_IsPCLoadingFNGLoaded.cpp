// PROFILE: game
// IsPCLoadingFNGLoaded, 14 bytes
bool IsFNGLoaded_(const char *fngName);

// FUNCTION: 0x004A9330
bool IsPCLoadingFNGLoaded()
{
	return IsFNGLoaded_("PC_Loading.fng");
}
