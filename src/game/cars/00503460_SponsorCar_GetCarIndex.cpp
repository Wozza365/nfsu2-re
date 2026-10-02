// PROFILE: game
// SponsorCar::GetCarIndex, 45 bytes
// yugecin's prototype: int __thiscall SponsorCar__GetCarIndex(struct SponsorCar *this);
#include "game/SponsorCar.h"
#include "game/CarPreset.h"
#include "game/Car.h"

CarPreset *FindCarPreset(unsigned int nameHash);
unsigned int cshash(char *str);
Car *FindCarByCarNameHash(unsigned int carNameHash);

// FUNCTION: 0x00503460
int SponsorCar::GetCarIndex()
{
	CarPreset *preset = FindCarPreset(carPresetHash);
	if (preset)
		return FindCarByCarNameHash(cshash(preset->modelName))->carIndex;
	return -1;
}
