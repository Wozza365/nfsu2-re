// PROFILE: game
// SmsMessageList::501480, 32 bytes
// yugecin's prototype: int __thiscall SmsMessageList__501480(struct SmsMessageList *this, int);
#include "game/SmsMessageList.h"

struct Obj8900D8 { int sub_5F41E0(int a1, int a2); };
extern Obj8900D8 *g_8900D8;

// FUNCTION: 0x00501480
int SmsMessageList::sub_501480(int a1)
{
	int result = g_8900D8->sub_5F41E0(13, a1);
	field_140C = 0;
	return result;
}
