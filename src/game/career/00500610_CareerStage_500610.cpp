// PROFILE: game
// CareerStage::500610, 83 bytes
// yugecin's prototype: int __thiscall CareerStage__500610(struct CareerStage *this);
#include "game/CareerStage.h"
#include "game/CareerStageSettings.h"

// FUNCTION: 0x00500610
bool CareerStage::sub_500610()
{
	if (signedSponsor)
		return false;
	CareerStageSettings *s = settings;
	if (s) {
		int n = CountNumField0Set();
		for (int i = 0; i < s->numSponsors; i++) {
			if (s->sponsors[i].sponsor && n >= s->field_1C[i])
				return true;
		}
	}
	return false;
}
