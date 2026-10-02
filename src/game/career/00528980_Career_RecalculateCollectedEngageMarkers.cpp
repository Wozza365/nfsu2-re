// PROFILE: game
// Career::RecalculateCollectedEngageMarkers, 102 bytes
// yugecin's prototype: void __thiscall Career__RecalculateCollectedEngageMarkers(struct Career *this);
// yugecin's note: zeros {struct Career+600}, finds all {enum MARKER_TYPE/0x12} and put them in {struct Career+600} if they're not collected (checked with {514E10}) ||| ref,ref,ref,ref
#include <string.h>
#include "game/Career.h"
#include "game/SmsMessageList.h"

struct PathsData { Marker *FindMarkerAtPosWithTypeAfterIndex(int a1, int type, Marker *after); };
extern PathsData g_88F298;  // pathsData

// FUNCTION: 0x00528980
void Career::RecalculateCollectedEngageMarkers()
{
	memset(collectedEngageMarkers, 0, sizeof(collectedEngageMarkers));
	int n = 0;
	for (Marker *m = g_88F298.FindMarkerAtPosWithTypeAfterIndex(0, 0x12, 0); m;
	     m = g_88F298.FindMarkerAtPosWithTypeAfterIndex(0, 0x12, m)) {
		if (n < 128 && g_85AD40.smsMessageList.IsEngageTipUncollected(m)) {
			collectedEngageMarkers[n] = m;
			n++;
		}
	}
}
