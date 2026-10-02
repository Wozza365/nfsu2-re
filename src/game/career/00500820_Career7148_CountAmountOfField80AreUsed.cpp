// PROFILE: game
// Career7148::CountAmountOfField80AreUsed, 86 bytes
// yugecin's prototype: int __thiscall Career7148__CountAmountOfField80AreUsed(struct Career7148 *this);
#include "game/Career7148.h"

// FUNCTION: 0x00500820
int Career7148::CountAmountOfField80AreUsed()
{
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (races[i * 8 + j])
				count++;
		}
	}
	return count;
}
