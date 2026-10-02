// PROFILE: game
// SponsorCar::ApplyTuningToInstance, 40 bytes
// yugecin's prototype: void __thiscall SponsorCar__ApplyTuningToInstance(struct SponsorCar *this, int playerIndex, struct MenuCarInstance *menuCarInstance, int);
#include "game/SponsorCar.h"
#include "game/MenuCarInstance.h"

// FUNCTION: 0x005039D0
void SponsorCar::ApplyTuningToInstance(int playerIndex, MenuCarInstance *menuCarInstance, int a3)
{
	GetCarIndex();
	menuCarInstance->ApplyCarPresetTuning(carPresetHash);
	menuCarInstance->CalculateSomeHashes(playerIndex + 1);
}
