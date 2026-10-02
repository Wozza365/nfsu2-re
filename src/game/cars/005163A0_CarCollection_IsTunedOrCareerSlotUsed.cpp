// PROFILE: game
// CarCollection::IsTunedOrCareerSlotUsed, 18 bytes
// yugecin's prototype: int __thiscall CarCollection__IsTunedOrCareerSlotUsed(struct CarCollection *this, unsigned int slotNameHash);
#include "game/CarCollection.h"

// FUNCTION: 0x005163A0
bool CarCollection::IsTunedOrCareerSlotUsed(unsigned int slotNameHash)
{
	return GetCareerOrTunedCarForSlotHash(slotNameHash) ? true : false;
}
