// PROFILE: game
// Career::5412D0, 70 bytes
// yugecin's prototype: int __thiscall Career__5412D0(struct Career *this);
#include "game/Career.h"

void sub_5001E0();

// FUNCTION: 0x005412D0
int Career::sub_5412D0()
{
	sub_532D80(cshash("DDAY_EVENT_B"));
	sub_5001E0();
	field_8704 = 0;
	field_8708 = 0;
	someCareerShop870C = 0;
	field_8710 = 0;
	sub_5331C0();
	return sub_533310();
}
