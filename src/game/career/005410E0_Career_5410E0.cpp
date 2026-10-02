// PROFILE: game
// Career::5410E0
// The game compiled this one with frame pointers (push ebp / mov ebp, esp), and knows ecx survives
// the call to sub_512F10 because it is earlier in the same jumbo file (src/game/zCareer.cpp).
#include "game/Career.h"
#include "game/Career7B00.h"
#include "game/CareerRace.h"

#pragma optimize("y", off)
// FUNCTION: 0x005410E0
int Career::sub_5410E0(CareerRace *race)
{
	field_8738 = race;
	sub_512F10(race->hash)->field_6 = 2;
	field_D24.sub_532EA0(race);
	return g_85AD40.field_887C.sub_524240(race);
}
#pragma optimize("", on)
