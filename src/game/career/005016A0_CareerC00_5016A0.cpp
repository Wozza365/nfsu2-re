// PROFILE: game
// CareerC00::5016A0, 47 bytes
// yugecin's prototype: int __thiscall CareerC00__5016A0(struct CareerC00 *this);
#include "game/CareerC00.h"

extern float g_865154;

// FUNCTION: 0x005016A0
void CareerC00::sub_5016A0()
{
	if (field_8 && field_11C == 1) {
		floatField_4 -= g_865154;
		if (floatField_4 <= 0.0f)
			sub_501600();
	}
}
