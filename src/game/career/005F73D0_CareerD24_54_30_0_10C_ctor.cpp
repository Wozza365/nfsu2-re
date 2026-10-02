// PROFILE: game
// CareerD24_54_30_0_10C::ctor, 61 bytes
// yugecin's prototype: struct CareerD24_54_30_0_10C *__cdecl CareerD24_54_30_0_10C__ctor(struct CareerD24_54_30_0_10C *this);
#include "game/CareerD24_54_30_0_10C.h"

// NONMATCHING (92%): the game stores field_8/C/14 = 0 both first and last; our compiler drops the
// second set as redundant. Something in the original (maybe a store through an aliasing pointer,
// or a member object) stopped that; not found yet.
// FUNCTION: 0x005F73D0
CareerD24_54_30_0_10C::CareerD24_54_30_0_10C()
{
	Clear();
	field_30 = 0;
	field_0 = 0;
	field_4 = 0;
	floatField_10 = -1.0f;
	field_18 = 0;
	field_1C = 0;
	field_20 = 0;
	field_24 = 0;
	field_28 = -1.0f;
	floatField_2C = 1;
	Clear();
}
