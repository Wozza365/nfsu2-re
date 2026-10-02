// PROFILE: game
// CareerStage::OnShowcaseDone, 66 bytes
// yugecin's prototype: int __thiscall CareerStage__OnShowcaseDone(struct CareerStage *this, void *);
// yugecin's note: magazine/dvd showcase (picture) done
#include "game/CareerStage.h"

struct Showcase { char pad[0x20]; unsigned int hash; };

// FUNCTION: 0x00541090
int CareerStage::OnShowcaseDone(void *a1)
{
	for (int i = 0; i < 6; i++) {
		if (!showcases[i] || showcases[i] == ((Showcase *)a1)->hash) {
			showcases[i] = ((Showcase *)a1)->hash;
			return IncrementStageIfFinished();
		}
	}
	return IncrementStageIfFinished();
}
