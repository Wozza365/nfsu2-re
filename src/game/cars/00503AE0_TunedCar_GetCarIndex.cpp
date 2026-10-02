// PROFILE: game
// TunedCar::GetCarIndex, 27 bytes
// yugecin's prototype: int __thiscall TunedCar__GetCarIndex(struct TunedCar *this);
// yugecin's note: NOTE: THIS IS SHARED FOR {struct TunedCar} {struct CareerCar} {struct OnlineCar} ||| ref,ref,ref
#include "game/TunedCar.h"
#include "game/Car.h"

Car *FindCarByCarNameHash(unsigned int carNameHash);

// FUNCTION: 0x00503AE0
int TunedCar::GetCarIndex()
{
	unsigned int hash = field_18.carNameHash;
	Car *car = FindCarByCarNameHash(hash);
	if (!car)
		return -1;
	return car->carIndex;
}
