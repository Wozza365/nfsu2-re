// PROFILE: game
// DebugTestFNGObject::MessageHandler, 32 bytes
void ShowFNG(const char *currentFNGName, const char *fngName, int a3);
struct DebugTestFNGObject {
	void *vtable; const char *fngName;
	void MessageHandler(unsigned int msg, int a2, int a3, int a4);
};

// FUNCTION: 0x0049CB90
void DebugTestFNGObject::MessageHandler(unsigned int msg, int a2, int a3, int a4)
{
	if (msg == 0x911AB364)
		ShowFNG(fngName, "UI_OptionsMain.fng", 0);
}
