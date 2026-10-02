// PROFILE: game
// SmsMessageList::529700, 65 bytes
// yugecin's prototype: void __thiscall SmsMessageList__529700(struct SmsMessageList *this);
#include "game/SmsMessageList.h"

struct C2 { int field_0; int field_4; int field_8; };
extern C2 *g_8900AC;
struct Obj8900D8 { int sub_5F41E0(int a1, int a2); };
extern Obj8900D8 *g_8900D8;
struct SoundEffectSystem { void PlaySound(int soundId); };
extern SoundEffectSystem *g_82B884;
extern signed char g_838119;

// FUNCTION: 0x00529700
void SmsMessageList::sub_529700()
{
	int v = 0;
	if (g_8900AC)
		v = g_8900AC->field_8;
	g_8900D8->sub_5F41E0(13, v);
	field_140C = 0;
	int sound = g_838119;
	if (sound != -1)
		g_82B884->PlaySound(sound);
}
