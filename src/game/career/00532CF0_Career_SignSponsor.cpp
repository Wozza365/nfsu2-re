// PROFILE: game
// Career::SignSponsor, 70 bytes
// yugecin's prototype: void __thiscall Career__SignSponsor(struct Career *this, struct CareerSponsor *sponsor);
// yugecin's note: what's the difference with {5417F0}? ||| ref
#include "game/Career.h"
#include "game/CareerSponsor.h"

// FUNCTION: 0x00532CF0
void Career::SignSponsor(CareerSponsor *sponsor)
{
	if (!stages[currentStage].signedSponsor) {
		UnlockNextLockedCarSlot();
		bank.money += sponsor->signingBonus;
		stages[currentStage].signedSponsor = sponsor;
	}
}
