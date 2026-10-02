// PROFILE: game
// Career::CountNumberOfSponsorsSigned, 95 bytes
// yugecin's prototype: int __thiscall Career__CountNumberOfSponsorsSigned(struct Career *this);
// yugecin's note: from {struct Career+72D8} to {struct Career+79F4}, add 1 if their {struct CareerStage+E8} is nonnull ||| ref,ref,ref
#include "game/Career.h"

// FUNCTION: 0x005009E0
int Career::CountNumberOfSponsorsSigned()
{
	int count = 0;
	for (int i = 0; i < 8; i++) {
		if (stages[i].signedSponsor)
			count++;
	}
	return count;
}
