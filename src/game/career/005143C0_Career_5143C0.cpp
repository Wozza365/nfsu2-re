// PROFILE: game
// NONMATCHING: sub_514340 gets inlined here (see that file).
// Career::5143C0, 64 bytes
// yugecin's prototype: int __thiscall Career__5143C0(struct Career *this, int, int);
#include "game/Career.h"
#include "game/CareerRace.h"

CareerRace *sub_4FFCF0(int a1, CareerRace *after);

// FUNCTION: 0x005143C0
bool Career::sub_5143C0(int a1, int a2)
{
	for (CareerRace *race = sub_4FFCF0(a1, 0); race; race = sub_4FFCF0(a1, race)) {
		if (sub_514340(race, a1))
			return true;
	}
	return false;
}
