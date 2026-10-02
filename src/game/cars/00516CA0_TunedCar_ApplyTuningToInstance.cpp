// PROFILE: game
// TunedCar::ApplyTuningToInstance, 35 bytes
// yugecin's prototype: void __thiscall TunedCar__ApplyTuningToInstance(struct TunedCar *this, int playerIndex, struct MenuCarInstance *menuCarInstance, int);
// yugecin's note: NOTE: THIS IS SHARED FOR {struct TunedCar} {struct CareerCar} {struct OnlineCar} ||| ref,ref,ref just calls {516AC0} ||| ref
#include "game/TunedCar.h"

// FUNCTION: 0x00516CA0
void TunedCar::ApplyTuningToInstance(int playerIndex, MenuCarInstance *menuCarInstance, int a3)
{
	GetCarIndex();
	field_18.ApplyTuningToInstance(playerIndex, menuCarInstance, a3);
}
