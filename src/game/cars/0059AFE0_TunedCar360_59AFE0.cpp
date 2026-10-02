// PROFILE: game
// TunedCar360::59AFE0, 115 bytes
#include <string.h>
#include "game/TunedCar360.h"

// FUNCTION: 0x0059AFE0
void TunedCar360::sub_59AFE0(int a1)
{
	if (a1 == -1) {
		memset(field_0, 100, sizeof(field_0));
		memset(field_17, 100, sizeof(field_17));
		memset(field_20, 100, sizeof(field_20));
		return;
	}
	if (a1 < 0x17) {
		sub_59AF80(0, a1, 0);
		return;
	}
	for (int i = 0; i < 9; i++) {
		if (a1 == 0x17)
			field_17[i] = 100;
		else if (a1 == 0x18)
			field_20[i] = 100;
	}
}
