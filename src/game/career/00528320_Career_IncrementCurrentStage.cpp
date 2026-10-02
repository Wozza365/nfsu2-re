// PROFILE: game
// Career::IncrementCurrentStage?, 69 bytes
// yugecin's prototype: int __thiscall Career__IncrementCurrentStage_(struct Career *this, int);
#include "game/Career.h"

#pragma optimize("y", off)
// FUNCTION: 0x00528320
void Career::IncrementCurrentStage(int stage)
{
	if (stage == currentStage) {
		int next = currentStage + 1;
		currentStage = next;
		if (!g_85AD40.field_887C.stage) {
			int v = 60000;
			g_85AD40.field_887C.sub_5111F0(&v, 12, 0);
		}
		g_85AD40.field_887C.stage = next;
	}
}
#pragma optimize("", on)
