// PROFILE: game
// CarCollection::GetFreeTunedCarSlot, 42 bytes
// yugecin's prototype: struct TunedCar *__thiscall CarCollection__GetFreeTunedCarSlot(struct CarCollection *this);
#include "game/CarCollection.h"

// Defined inline in CarCollection.h (HasFreeEntryInTunedCars inlines it); this emits the out-of-line copy.
// FUNCTION: 0x005036C0 SYMBOL=?GetFreeTunedCarSlot@CarCollection@@QAEPAUTunedCar@@XZ
typedef TunedCar *(CarCollection::*GetFreeTunedCarSlotFn)();
GetFreeTunedCarSlotFn emit_GetFreeTunedCarSlot() { return &CarCollection::GetFreeTunedCarSlot; }
