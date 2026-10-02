// PROFILE: game
// Career7148::HasSomething5007E0, 51 bytes
// yugecin's prototype: int __thiscall Career7148__HasSomething5007E0(struct Career7148 *this, void *);
#include "game/Career7148.h"
#include "game/CareerRace.h"

// FUNCTION: 0x005007E0
bool Career7148::HasSomething5007E0(CareerRace *race)
{
	for (int i = 0; i < 64; i++) {
		if (races[i] && races[i]->hash == race->hash)
			return true;
	}
	return false;
}
