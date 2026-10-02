// PROFILE: game
extern int g_8383A8;
void DoNextBootFlowEntry(void *a, int b);
struct LSBlankMovieFNGObject {
	void *vtable; void *f4;
	void MessageHandler(unsigned int msg, int a2, int a3, int a4);
};
// FUNCTION: 0x004C53A0
void LSBlankMovieFNGObject::MessageHandler(unsigned int msg, int a2, int a3, int a4)
{
	if (msg == 0xC3960EB9) {
		g_8383A8 = 1;
		DoNextBootFlowEntry(f4, a3);
	}
}
