// PROFILE: game
// Career::532C20, 64 bytes
// yugecin's prototype: int __thiscall Career__532C20(struct Career *this, void *);
#include "game/Career.h"
#include "game/CareerRace.h"

// FUNCTION: 0x00532C20
bool Career::sub_532C20(CareerRace *race)
{
	if (!race->field_7F && field_7148.HasSomething5007E0(race)) {
		if (race->field_D != 1)
			return true;
		return sub_527890() ? true : false;
	}
	return false;
}
