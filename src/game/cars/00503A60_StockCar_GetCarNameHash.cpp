// PROFILE: game
// StockCar::GetCarNameHash, 30 bytes
// yugecin's prototype: unsigned int __thiscall StockCar__GetCarNameHash(struct StockCar *this);
#include "game/StockCar.h"
#include "game/Car.h"

extern Car *ptrCarData;

// FUNCTION: 0x00503A60
unsigned int StockCar::GetCarNameHash()
{
	Car *car = &ptrCarData[indexInCarData];
	if (car)
		return car->carNamehash;
	return -1;
}
