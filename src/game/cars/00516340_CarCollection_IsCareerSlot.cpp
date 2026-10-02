// PROFILE: game
// CarCollection::IsCareerSlot, 18 bytes
// yugecin's prototype: int __thiscall CarCollection__IsCareerSlot(struct CarCollection *this, unsigned int slotNameHash);
#include "game/CarCollection.h"

// FUNCTION: 0x00516340
bool CarCollection::IsCareerSlot(unsigned int slotNameHash)
{
	return GetCareerCarForSlotHash(slotNameHash) ? true : false;
}
