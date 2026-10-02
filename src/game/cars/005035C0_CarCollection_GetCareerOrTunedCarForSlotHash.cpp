// PROFILE: game
// CarCollection::GetCareerOrTunedCarForSlotHash, 114 bytes
// yugecin's prototype: struct TunedCar *__thiscall CarCollection__GetCareerOrTunedCarForSlotHash(struct CarCollection *this, unsigned int slotNameHash);
// yugecin's note: may not modify ecx! see 52A736
#include "game/CarCollection.h"
#include "game/CareerCar.h"
#include "game/TunedCar.h"

// FUNCTION: 0x005035C0
TunedCar *CarCollection::GetCareerOrTunedCarForSlotHash(unsigned int slotNameHash)
{
	for (int i = 0; i < 20; i++) {
		if (tunedCars[i].slotHash && tunedCars[i].slotHash == slotNameHash)
			return &tunedCars[i];
	}
	for (int j = 0; j < numCareerCarSlots; j++) {
		if (careerCars[j].slotHash == slotNameHash)
			return &careerCars[j];
	}
	return 0;
}
