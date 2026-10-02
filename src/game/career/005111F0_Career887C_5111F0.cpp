// PROFILE: game
// Career887C::5111F0, 77 bytes
// yugecin's prototype: int __thiscall Career887C__5111F0(struct Career887C *this, int *, int, int);
#include "game/Career887C.h"

// FUNCTION: 0x005111F0
void Career887C::sub_5111F0(int *a1, int a2, int a3)
{
	for (int i = 0; i != 8; i++) {
		if (!field_A8[i].field_4) {
			field_A8[i].field_0 = *a1;
			field_A8[i].field_4 = a2;
			field_A8[i].field_8 = a3;
			return;
		}
	}
}
