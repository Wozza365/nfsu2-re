// PROFILE: game
// TunedCar::GetCarNameHash, 4 bytes
// yugecin's prototype: unsigned int __thiscall TunedCar__GetCarNameHash(struct TunedCar *this);
// yugecin's note: NOTE: THIS IS SHARED FOR {struct TunedCar} {struct CareerCar} {struct OnlineCar} ||| ref,ref,ref
#include "game/TunedCar.h"

// FUNCTION: 0x00503B00
unsigned int TunedCar::GetCarNameHash()
{
	return field_18.carNameHash;
}
