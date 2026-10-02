// PROFILE: game
// Career::500B80, 72 bytes
// yugecin's prototype: int __thiscall Career__500B80(struct Career *this, unsigned int hash);
// yugecin's note: checks if something is collected ({struct Career7B00.6}) ||| ref
#include "game/Career.h"

// FUNCTION: 0x00500B80
bool Career::sub_500B80(unsigned int hash)
{
	Career7B00 *e = FindCareer7B00WithHash0(hash);
	if (e)
		return e->field_6 == 1;
	return false;
}
