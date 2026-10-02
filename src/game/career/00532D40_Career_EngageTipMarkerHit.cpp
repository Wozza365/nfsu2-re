// PROFILE: game
// Career::EngageTipMarkerHit, 51 bytes
// yugecin's prototype: void __thiscall Career__EngageTipMarkerHit(struct Career *this, struct Marker *marker);
// yugecin's note: Implementation:  .controlchars [] .pushmode pre [struct SmsData] *smsdata; ||| ref  smsdata = this->[struct Career+5D20]->[529C40](engageMarker); ||| ref,ref if (smsdata) {         this->[struct Caree
#include "game/Career.h"
#include "game/SmsData.h"

// FUNCTION: 0x00532D40
void Career::EngageTipMarkerHit(Marker *marker)
{
	SmsData *data = smsMessageList.SendEngageTipSmsMessage(marker);
	if (data) {
		bank.money += data->moneyReward;
		RecalculateCollectedEngageMarkers();
	}
}
