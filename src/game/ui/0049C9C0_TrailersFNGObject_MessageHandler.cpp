// PROFILE: game
// TrailersFNGObject::MessageHandler, 40 bytes
void ShowFNG(const char *currentFNGName, const char *fngName, int a3);
struct TrailersFNGObject {
	void *vtable; const char *fngName;
	void MessageHandler(unsigned int msg, int a2, int a3, int a4);
};

// FUNCTION: 0x0049C9C0
void TrailersFNGObject::MessageHandler(unsigned int msg, int a2, int a3, int a4)
{
	if (msg == 0x911AB364 || msg == 0xC3960EB9)
		ShowFNG(fngName, "UI_Options.fng", 0);
}
