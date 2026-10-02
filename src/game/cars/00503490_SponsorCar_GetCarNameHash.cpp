// PROFILE: game
// SponsorCar::GetCarNameHash, 33 bytes
// yugecin's prototype: unsigned int __thiscall SponsorCar__GetCarNameHash(struct SponsorCar *this);
#include "game/SponsorCar.h"
#include "game/CarPreset.h"

CarPreset *FindCarPreset(unsigned int nameHash);
unsigned int cshash(char *str);

// FUNCTION: 0x00503490
unsigned int SponsorCar::GetCarNameHash()
{
	CarPreset *preset = FindCarPreset(carPresetHash);
	if (preset)
		return cshash(preset->modelName);
	return -1;
}
