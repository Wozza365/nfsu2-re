// PROFILE: game
// CarCollection::IsStockCar, 56 bytes
// yugecin's prototype: int __thiscall CarCollection__IsStockCar(struct CarCollection *this, unsigned int slotHash);
// yugecin's note: may not modify ecx! see 52A7A5
#include "game/CarCollection.h"

// FUNCTION: 0x00516360
bool CarCollection::IsStockCar(unsigned int slotHash)
{
	if (FindStockCar(slotHash))
		return true;
	return false;
}
