// PROFILE: game
// CarCollection::GetCareerCarForSlotHash, 64 bytes
// yugecin's prototype: struct CareerCar *__thiscall CarCollection__GetCareerCarForSlotHash(struct CarCollection *this, unsigned int slotHash);
#include "game/CarCollection.h"

// FUNCTION: 0x00503680
CareerCar *CarCollection::GetCareerCarForSlotHash(unsigned int slotHash)
{
	for (int i = 0; i < numCareerCarSlots; i++) {
		if (careerCars[i].slotHash == slotHash)
			return &careerCars[i];
	}
	return 0;
}
