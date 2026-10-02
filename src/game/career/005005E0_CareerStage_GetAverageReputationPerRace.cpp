// PROFILE: game
// CareerStage::GetAverageReputationPerRace, 35 bytes
// yugecin's prototype: float __thiscall CareerStage__GetAverageReputationPerRace(struct CareerStage *this);
#include "game/CareerStage.h"

// EQUIVALENT: identical instructions, but the original encodes the stack slot as [esp+0] with an
// explicit 8-bit zero offset (4-byte forms) where our compiler uses the short [esp] form. Game code
// uses both encodings about equally; what decides it isn't known yet. Dividing by a double gives the
// original's fld/fidiv order (a float divide gives fild/fdivr).
// FUNCTION: 0x005005E0 EQUIVALENT
float CareerStage::GetAverageReputationPerRace()
{
	if (racesFinished > 0)
		return totalReputation / (double) racesFinished;
	return 0.0f;
}
