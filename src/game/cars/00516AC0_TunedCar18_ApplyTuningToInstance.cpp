// PROFILE: game
// TunedCar18::ApplyTuningToInstance, 100 bytes
// yugecin's prototype: void __thiscall TunedCar18__ApplyTuningToInstance(struct TunedCar18 *this, int playerIndex, struct MenuCarInstance *menuCarInstance, int);
#include "game/TunedCar18.h"
#include "game/MenuCarInstance.h"

// FUNCTION: 0x00516AC0
void TunedCar18::ApplyTuningToInstance(int playerIndex, MenuCarInstance *menuCarInstance, int a3)
{
	sub_503880(playerIndex, menuCarInstance);
	TunedCar360 tuning;
	tuning = field_348[a3];
	menuCarInstance->field_10.field_374.field_14 = tuning;
	menuCarInstance->sub_639CE0(0, 1, 1, 1);
}
