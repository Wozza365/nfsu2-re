// PROFILE: game
// Career::500C30, 46 bytes
// yugecin's prototype: int __thiscall Career__500C30(struct Career *this, int);
#include "game/Career.h"
#include "game/CareerRace.h"
#include "game/CareerSponsor.h"

// FUNCTION: 0x00500C30
int Career::sub_500C30(CareerRace *race)
{
	if (race->raceRewardType == 1) {
		CareerSponsor *sponsor = stages[currentStage].signedSponsor;
		if (sponsor)
			return sponsor->bankRewardPerSponsorRace;
	}
	return race->bankToWinFromRace;
}
