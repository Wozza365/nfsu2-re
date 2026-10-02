// PROFILE: game
// Career::GetCarForActiveCareerCarSlot, 18 bytes
// yugecin's prototype: struct CareerCar *__thiscall Career__GetCarForActiveCareerCarSlot(struct Career *this);
// yugecin's note: .pushmode pre return {503680}(this->{struct Career+8740}); ||| ref,ref .popmode pre
#include "game/Career.h"
#include "game/CarCollection.h"

extern CarCollection g_83AD90;

// FUNCTION: 0x00513C30
CareerCar *Career::GetCarForActiveCareerCarSlot()
{
	return g_83AD90.GetCareerCarForSlotHash(activeCarSlotHash);
}
