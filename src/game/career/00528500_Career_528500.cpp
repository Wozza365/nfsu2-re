// PROFILE: game
// Career::528500, 93 bytes
// yugecin's prototype: int __thiscall Career__528500(struct Career *this, unsigned int hash);
#include "game/Career.h"
#include "game/CareerRace.h"

CareerRace *FindCareerRaceByHash(unsigned int raceHash);

// FUNCTION: 0x00528500
void Career::sub_528500(unsigned int hash)
{
	Career7B00 *e = FindCareer7B00WithHash0(hash);
	if (e->field_6 != 1)
		e->field_6 = 4;
	field_887C.sub_5242C0(FindCareerRaceByHash(hash), 0);
}
