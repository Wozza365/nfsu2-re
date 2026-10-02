// PROFILE: game
// Career::500F30, 67 bytes
// yugecin's prototype: int __thiscall Career__500F30(struct Career *this);
// yugecin's note: nulls {struct Career+0}, {struct Career+600}, {struct Career+800} ||| ref,ref,ref
#include <string.h>
#include "game/Career.h"

// FUNCTION: 0x00500F30
void Career::sub_500F30()
{
	for (int i = 0; i < 64; i++) {
		field_0[i].field_0 = 0;
		field_0[i].field_4 = 0;
		field_0[i].careerShop8 = 0;
		field_0[i].field_C = 0;
		field_0[i].field_10 = 0;
	}
	memset(collectedEngageMarkers, 0, sizeof(collectedEngageMarkers));
	memset(collectedMoneyMarkers_, 0, sizeof(collectedMoneyMarkers_));
}
