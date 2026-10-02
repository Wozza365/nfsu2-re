// PROFILE: game
// Career::527890, 94 bytes
// yugecin's prototype: int __thiscall Career__527890(struct Career *this);
// Career::527890, 94 bytes
// yugecin's prototype: int __thiscall Career__527890(struct Career *this);
// yugecin's note: doesn't use this; something with cars
#include "game/Career.h"
#include "game/CareerCar.h"
#include "game/Car.h"

struct CarCollectionWithPointers {
	InventoryCar *FindCarWithFlagAfterGivenCar(int flag, InventoryCar *after);
};
extern CarCollectionWithPointers g_83AD90;
extern Car *g_8A1CCC;  // ptrCarData

static inline bool CarIs88A(CareerCar *car)
{
	Car *data = &g_8A1CCC[car->GetCarIndex()];
	if (!data)
		return false;
	return data->field_88A != 0;
}

// FUNCTION: 0x00527890
bool Career::sub_527890()
{
	for (CareerCar *car = (CareerCar *)g_83AD90.FindCarWithFlagAfterGivenCar(4, 0); car;
	     car = (CareerCar *)g_83AD90.FindCarWithFlagAfterGivenCar(4, car)) {
		if (car->hasCarBought && CarIs88A(car))
			return true;
	}
	return false;
}
