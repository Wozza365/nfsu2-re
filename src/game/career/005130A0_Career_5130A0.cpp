// PROFILE: game
// Career::5130A0, 100 bytes
// yugecin's prototype: int __thiscall Career__5130A0(struct Career *this, int);
#include "game/Career.h"
#include "game/CareerRace.h"

extern CareerRace *g_8383E0;  // careerRaces
extern int g_8383E4;  // numCareerRaces

static inline CareerRace *GetCareerRace(int i)
{
	if (i >= 0 && i < g_8383E4)
		return &g_8383E0[i];
	return 0;
}

// FUNCTION: 0x005130A0
bool Career::sub_5130A0(int stage)
{
	for (int i = 0; i < g_8383E4; i++) {
		CareerRace *race = GetCareerRace(i);
		if (race && race->stageIndex == stage && !sub_500B80(race->hash))
			return false;
	}
	return true;
}
