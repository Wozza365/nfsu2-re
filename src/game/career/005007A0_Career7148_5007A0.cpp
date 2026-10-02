// PROFILE: game
// Career7148::5007A0, 61 bytes
// yugecin's prototype: void __thiscall Career7148__5007A0(struct Career7148 *this, struct CareerRace *race);
#include "game/Career7148.h"
#include "game/CareerRace.h"

// Calls the static GetRaceCategory (5002E0) with the race in eax; see src/game/zCareer.cpp.
// FUNCTION: 0x005007A0
void Career7148::sub_5007A0(CareerRace *race)
{
	int category = GetRaceCategory(race);
	field_180.field_0[category]++;
	for (int i = 0; i < 64; i++) {
		if (!races[i]) {
			races[i] = race;
			return;
		}
	}
}
