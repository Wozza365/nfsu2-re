// PROFILE: game
// Career::GetBankWonFromRace, 79 bytes
// yugecin's prototype: int __thiscall Career__GetBankWonFromRace(struct Career *this);
// yugecin's note: calculates in possible sponsor bonus money TODO: this returns 0 on some conditions. what are they?
#include "game/Career.h"
#include "game/CareerRace.h"
#include "game/CareerSponsor.h"

// FUNCTION: 0x00532E50
int Career::GetBankWonFromRace()
{
	if (g_85AD40.currentRace_lastRace_ && field_D24.sub_5287A0(0)) {
		CareerRace *race = currentRace_lastRace_;
		if (race->raceRewardType == 1) {
			CareerSponsor *sponsor = stages[currentStage].signedSponsor;
			if (sponsor)
				return sponsor->bankRewardPerSponsorRace;
		}
		return race->bankToWinFromRace;
	}
	return 0;
}
