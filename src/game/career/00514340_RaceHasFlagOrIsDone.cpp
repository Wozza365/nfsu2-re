// PROFILE: game
// NONMATCHING: our compiler inlines this into its only caller (5143C0) and does not inline
// FindCareer7B00WithHash0 here; the game does the opposite. The register convention (race in edx,
// id in edi) also comes out differently. A second caller, other orders and inline hints did not help.
// sub_514340, 114 bytes
#include "game/Career.h"
#include "game/CareerRace.h"

static inline bool HasField18Flag2(CareerRace *race, int id)
{
	for (int i = 0; i < race->numField18; i++) {
		if (race->field_18[i].field_0 == id)
			return (race->field_18[i].field_2 & 2) == 2;
	}
	return false;
}

// Static helper with a custom calling convention (race in edx, id in edi): only matches inside
// src/game/zCareer.cpp, next to its one caller (5143C0) and FindCareer7B00WithHash0, which it inlines.
// FUNCTION: 0x00514340
static bool sub_514340(CareerRace *race, int id)
{
	if (!race)
		return true;
	if (HasField18Flag2(race, id))
		return true;
	Career7B00 *e = g_85AD40.FindCareer7B00WithHash0(race->hash);
	if (!e)
		return false;
	return e->field_6 == 1 ? true : false;
}
