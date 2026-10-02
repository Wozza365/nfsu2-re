// PROFILE: game
// CareerStage::GetCareerSponsorAtIndex, 34 bytes
// yugecin's prototype: struct CareerSponsor *__thiscall CareerStage__GetCareerSponsorAtIndex(struct CareerStage *this, int index);
#include "game/CareerStage.h"
#include "game/CareerStageSettings.h"

// FUNCTION: 0x005006D0
CareerSponsor *CareerStage::GetCareerSponsorAtIndex(int index)
{
	if (index >= 0 && index < settings->numSponsors)
		return settings->sponsors[index].sponsor;
	return 0;
}
