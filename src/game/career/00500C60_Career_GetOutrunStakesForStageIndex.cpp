// PROFILE: game
// Career::GetOutrunStakesForStageIndex, 52 bytes
// yugecin's prototype: int __thiscall Career__GetOutrunStakesForStageIndex(struct Career *this, int stageIndex);
// yugecin's note: stakes: amount to win or lose stageIndex 0-7
#include "game/Career.h"
#include "game/CareerStageSettings.h"

// FUNCTION: 0x00500C60
int Career::GetOutrunStakesForStageIndex(int stageIndex)
{
	CareerStageSettings *settings = GetStage(stageIndex)->settings;
	if (settings)
		return settings->outrunStakes;
	return 0;
}
