// PROFILE: game
// Career4210::514810, 65 bytes
// yugecin's prototype: void __thiscall Career4210__514810(struct Career4210 *this);
#include "game/Career4210.h"

extern int g_8654A4;
extern int g_89E7B0;
extern float g_865154;

// FUNCTION: 0x00514810
void Career4210::sub_514810()
{
	if (g_8654A4 == 6 && !g_89E7B0 && field_6 && field_10) {
		floatField_18 -= g_865154;
		if (floatField_18 < 0.0f)
			floatField_18 = 0.0f;
	}
}
