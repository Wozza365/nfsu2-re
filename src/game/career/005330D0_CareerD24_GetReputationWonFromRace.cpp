// PROFILE: game
// CareerD24::GetReputationWonFromRace, 49 bytes
#include "game/CareerD24.h"

extern CareerRace *g_863470;
float CalculateReputationToAddFromWonRace(float a1, CareerRace *race);

// FUNCTION: 0x005330D0
float CareerD24::GetReputationWonFromRace()
{
	if (!sub_5287A0(0))
		return 0.0f;
	return CalculateReputationToAddFromWonRace(sub_513FE0(), g_863470);
}
