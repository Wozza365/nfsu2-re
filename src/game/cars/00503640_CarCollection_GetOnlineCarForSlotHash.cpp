// PROFILE: game
// CarCollection::GetOnlineCarForSlotHash, 63 bytes
// yugecin's prototype: struct OnlineCar *__thiscall CarCollection__GetOnlineCarForSlotHash(struct CarCollection *this, unsigned int slotHash);
#include "game/CarCollection.h"

// FUNCTION: 0x00503640
OnlineCar *CarCollection::GetOnlineCarForSlotHash(unsigned int slotHash)
{
	for (int i = 0; i < 6; i++) {
		if (onlineCars[i].slotHash && onlineCars[i].slotHash == slotHash)
			return &onlineCars[i];
	}
	return 0;
}
