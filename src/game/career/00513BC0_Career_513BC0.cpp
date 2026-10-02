// PROFILE: game
// Career::513BC0, 42 bytes
// yugecin's prototype: int __thiscall Career__513BC0(struct Career *this);
#include "game/Career.h"

extern int g_89E7B0;

// FUNCTION: 0x00513BC0
void Career::sub_513BC0()
{
	if (g_89E7B0 == 0 && !field_873D && field_713C.field_0 != 9)
		field_713C.sub_5023F0();
}
