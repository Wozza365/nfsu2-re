// PROFILE: game
// CarCollection::IsSponsorCar, 39 bytes
// yugecin's prototype: int __thiscall CarCollection__IsSponsorCar(struct CarCollection *this, unsigned int slotNameHash);
#include "game/CarCollection.h"

// FUNCTION: 0x00503590
bool CarCollection::IsSponsorCar(unsigned int slotNameHash)
{
	for (int i = 0; i < 12; i++) {
		if (slotNameHash == sponsorCars[i].slotHash)
			return true;
	}
	return false;
}
