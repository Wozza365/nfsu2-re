// PROFILE: game
// Career::FindRaceByHash, 16 bytes
// yugecin's prototype: struct CareerRace *__thiscall Career__FindRaceByHash(struct Career *this, unsigned int raceHash);
// yugecin's note: basically __stdcall wrapper around {4FFC90} because 'this' is not used ||| ref
#include "game/Career.h"

CareerRace *FindCareerRaceByHash(unsigned int raceHash);

// FUNCTION: 0x005003F0
CareerRace *Career::FindRaceByHash(unsigned int raceHash)
{
	return FindCareerRaceByHash(raceHash);
}
