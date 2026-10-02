// PROFILE: game
// Career::SetActiveCarBySlotHash, 20 bytes
// yugecin's prototype: void __thiscall Career__SetActiveCarBySlotHash(struct Career *this, unsigned int hash);
// yugecin's note: also sets {this->{struct Career+873D} = 1} ||| code,ref
#include "game/Career.h"

// FUNCTION: 0x00500BD0
void Career::SetActiveCarBySlotHash(unsigned int hash)
{
	field_873D = 1;
	activeCarSlotHash = hash;
}
