// PROFILE: game
// sub_5002E0, 67 bytes
// yugecin's note: {struct CareerRace} passed in eax! (fastcall?) ||| ref return 0/1/2/3/4/5/7
#include "game/CareerRace.h"

// NOHOOK: static (internal linkage), so the loader's hook table cannot name it; 5007A0 uses our copy.
// Static helper: the game passes the race in eax (a custom calling convention the compiler gives
// static functions whose callers it can see), so it only matches inside src/game/zCareer.cpp.
// FUNCTION: 0x005002E0 NOHOOK
static int GetRaceCategory(CareerRace *race)
{
	if (race->field_D == 1)
		return 7;
	if (race->raceRewardType == 2)
		return 5;
	switch (race->raceType) {
	case 0:
		return 0;
	case 1:
		return 4;
	case 2:
		return 2;
	case 4:
		return 1;
	case 5:
		return 3;
	}
	return 0;
}
