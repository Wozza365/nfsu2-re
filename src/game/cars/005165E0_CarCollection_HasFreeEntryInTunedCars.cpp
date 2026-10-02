// PROFILE: game
// CarCollection::HasFreeEntryInTunedCars, 51 bytes
// yugecin's prototype: int __thiscall CarCollection__HasFreeEntryInTunedCars(struct CarCollection *this);
// yugecin's note: may not modify ecx! see 52A736 and 52A7A5
#include "game/CarCollection.h"

// FUNCTION: 0x005165E0
bool CarCollection::HasFreeEntryInTunedCars()
{
	if (!GetFreeTunedCarSlot())
		return false;
	return true;
}
