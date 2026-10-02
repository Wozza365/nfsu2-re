// PROFILE: game
// CareerCar434::503D50, 66 bytes
// yugecin's prototype: int __thiscall CareerCar434__503D50(struct CareerCar434 *this, int, int);
#include "game/CareerCar434.h"
// FUNCTION: 0x00503D50
void CareerCar434::sub_503D50(int a1, int a2)
{
	bool skip = false;
	switch (a1) {
	case 0x3F: case 0x44: case 0x45: case 0x46: case 0x47: case 0x49:
		skip = true;
		break;
	case 0x40: case 0x41: case 0x42: case 0x43: case 0x48:
		skip = false;
		break;
	}
	if (skip)
		return;
	int bit = 0;
	*sub_503B10(a1, a2, &bit) |= 1 << bit;
}
