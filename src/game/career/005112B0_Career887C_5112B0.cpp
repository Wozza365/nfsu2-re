// PROFILE: game
// Career887C::5112B0, 58 bytes
// yugecin's prototype: int __thiscall Career887C__5112B0(struct Career887C *this);
#include "game/Career887C.h"

struct Obj46D100 { bool sub_46D100(int a1); };
struct Obj82BA30 { char pad[0x2c]; Obj46D100 *field_2C; };
extern Obj82BA30 *g_82BA30;

// FUNCTION: 0x005112B0
bool Career887C::sub_5112B0()
{
	if (g_82BA30 && g_82BA30->field_2C) {
		Obj46D100 *obj = g_82BA30->field_2C;
		return obj->sub_46D100(0) && !obj->sub_46D100(1);
	}
	return true;
}
