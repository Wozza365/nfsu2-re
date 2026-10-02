// PROFILE: game
// Career::UnlockNextLockedCarSlot, 48 bytes
// yugecin's prototype: void __thiscall Career__UnlockNextLockedCarSlot(struct Career *this);
// yugecin's note: 'this' is unused; can be treated as a normal __stdcall (__cdecl even)  finds first career car in {83A9D0.3C0.5954} with nonzero {struct CareerCar+7F4} and puts it on zero ||| ref,ref
#include "game/Career.h"
#include "game/CarCollection.h"

extern CarCollection g_83AD90;

// FUNCTION: 0x005284D0
void Career::UnlockNextLockedCarSlot()
{
	for (int i = 0; i < g_83AD90.numCareerCarSlots; i++) {
		if (g_83AD90.careerCars[i].isLocked) {
			g_83AD90.careerCars[i].isLocked = 0;
			return;
		}
	}
}
