// PROFILE: game
// Career::500A40, 93 bytes
// yugecin's prototype: int __thiscall Career__500A40(struct Career *this, int stage);
// yugecin's note: {83A9D0.20370.7AF8} is usually passed as arg0 ||| ref
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

// FUNCTION: 0x00500A40
int Career::sub_500A40(int stage)
{
	int result = -1;
	for (int i = 0; i < g_8383E4; i++) {
		CareerRace *race = GetCareerRace(i);
		if (race->stageIndex == stage && race->raceRewardType == 2 && result == -1)
			result = race->bankToWinFromRace;
	}
	if (result == -1)
		return 0;
	return result;
}
