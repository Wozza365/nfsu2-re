// PROFILE: game
// StockCar::GetCarIndex, 4 bytes
// yugecin's prototype: int __thiscall StockCar__GetCarIndex(struct StockCar *this);
#include "game/StockCar.h"

// FUNCTION: 0x00503A30
int StockCar::GetCarIndex()
{
	return indexInCarData;
}
