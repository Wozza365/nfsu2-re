// PROFILE: game
// Career::541120, 63 bytes
// yugecin's prototype: int __thiscall Career__541120(struct Career *this, int);
#include "game/Career.h"

struct Obj81CBC0 { void sub_4131F0(); };
extern Obj81CBC0 g_81CBC0;
extern unsigned char g_8385B9;
extern unsigned int g_8385A0;
extern unsigned int g_8385A4;
extern unsigned char g_8385B8;
extern unsigned int g_838590;

// The game compiled this one with frame pointers (push ebp / mov ebp, esp).
#pragma optimize("y", off)
// FUNCTION: 0x00541120
int Career::sub_541120(int a1)
{
	g_81CBC0.sub_4131F0();
	g_8385B9 = 0;
	g_8385A0 = 0;
	g_8385A4 = 0;
	g_8385B8 = 0;
	g_838590 = 0;
	return field_C00.sub_533BE0(a1);
}
#pragma optimize("", on)
