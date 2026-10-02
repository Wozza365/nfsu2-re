// PROFILE: game
// Career::500460, 75 bytes
// yugecin's prototype: int __thiscall Career__500460(struct Career *this, void *);
#include "game/Career.h"

struct Obj38 { unsigned char pad[0x38]; unsigned int hash; };

// FUNCTION: 0x00500460
bool Career::sub_500460(void *a1)
{
	unsigned int hash = ((Obj38 *)a1)->hash;
	Career7B00 *e = FindCareer7B00WithHash0(hash);
	if (e && e->field_6 == 5)
		return true;
	return false;
}
