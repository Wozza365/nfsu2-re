// PROFILE: game
// Career7148::513770, 73 bytes
// yugecin's prototype: int __thiscall Career7148__513770(struct Career7148 *this, int);
#include "game/Career7148.h"

// FUNCTION: 0x00513770
int Career7148::sub_513770(int a1)
{
	int count = 0;
	for (int i = 0; i < 64; i++) {
		if (races[i] && sub_513600(races[i], a1))
			count++;
	}
	return count;
}
