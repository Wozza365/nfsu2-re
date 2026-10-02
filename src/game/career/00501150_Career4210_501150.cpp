// PROFILE: game
// Career4210::501150, 69 bytes
// yugecin's prototype: int __thiscall Career4210__501150(struct Career4210 *this, int);
#include "game/Career4210.h"
#include "game/Career.h"
struct Race20 { char pad[0x20]; unsigned int hash; };
#pragma optimize("y", off)
// FUNCTION: 0x00501150
bool Career4210::sub_501150(void *a1)
{
	unsigned int hash = ((Race20 *)a1)->hash;
	Career7B00 *e = g_85AD40.FindCareer7B00WithHash0(hash);
	if (e && e->field_4 == 2)
		return e->field_6 != 1 ? true : false;
	return false;
}
#pragma optimize("", on)
