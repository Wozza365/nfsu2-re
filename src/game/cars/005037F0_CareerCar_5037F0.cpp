// PROFILE: game
// CareerCar::5037F0, 34 bytes
// yugecin's prototype: int __thiscall CareerCar__5037F0(struct CareerCar *this);
#include "game/CareerCar.h"
#include "game/Car.h"

extern Car *ptrCarData;

// FUNCTION: 0x005037F0
bool CareerCar::sub_5037F0()
{
	Car *car = &ptrCarData[GetCarIndex()];
	if (car)
		return car->field_88A ? true : false;
	return false;
}
