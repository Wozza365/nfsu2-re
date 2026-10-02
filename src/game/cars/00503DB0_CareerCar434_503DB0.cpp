// PROFILE: game
// CareerCar434::503DB0, 74 bytes
#include "game/CareerCar434.h"

// FUNCTION: 0x00503DB0
bool CareerCar434::sub_503DB0(int a1, int a2)
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
		return false;
	int bit = 0;
	return (*sub_503B10(a1, a2, &bit) & (1 << bit)) ? true : false;
}
