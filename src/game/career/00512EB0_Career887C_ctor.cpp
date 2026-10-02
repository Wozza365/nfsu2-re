// PROFILE: game
// NONMATCHING: only the memset setup is scheduled differently (the game zeroes eax after the store to
// field_118 and loads edi before ecx). memset(&a[0]), loops and a for loop over field_A8 did not help.
// Career887C::ctor, 84 bytes
// yugecin's prototype: int __thiscall Career887C__ctor(struct Career887C *this);
#include <string.h>
#include "game/Career887C.h"
// FUNCTION: 0x00512EB0
Career887C::Career887C()
{
	field_20 = 0;
	int i = 0;
	do {
		field_A8[i].field_0 = 0;
		i++;
	} while (i < 8);
	field_108 = 0;
	field_10C = 0;
	field_110 = 0;
	field_114 = 0;
	field_118 = 0;
	field_11C = 0;
	memset(field_120, 0, sizeof(field_120));
}
