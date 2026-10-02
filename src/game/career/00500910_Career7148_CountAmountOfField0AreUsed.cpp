// PROFILE: game
// Career7148::CountAmountOfField0AreUsed, 86 bytes
// yugecin's prototype: int __thiscall Career7148__CountAmountOfField0AreUsed(struct Career7148 *this);
#include "game/Career7148.h"

// FUNCTION: 0x00500910
int Career7148::CountAmountOfField0AreUsed()
{
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (field_0[i * 8 + j])
				count++;
		}
	}
	return count;
}
