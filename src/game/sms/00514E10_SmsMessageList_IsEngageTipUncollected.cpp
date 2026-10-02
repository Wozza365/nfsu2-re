// PROFILE: game
// SmsMessageList::IsEngageTipUncollected, 98 bytes
// yugecin's prototype: int __thiscall SmsMessageList__IsEngageTipUncollected(struct SmsMessageList *this, struct Marker *marker);
// yugecin's note: marker is of type {enum MARKER_TYPE/0x12} ||| ref
#include "game/SmsMessageList.h"
#include "game/SmsData.h"

struct Marker { unsigned char pad[0x30]; unsigned int hash; };
extern SmsData *g_838454;  // smsDatas
extern int g_838450;  // numSmsDatas

static inline SmsData *GetSmsData(int i)
{
	if (i >= 0 && i < g_838450)
		return &g_838454[i];
	return 0;
}

// FUNCTION: 0x00514E10
bool SmsMessageList::IsEngageTipUncollected(Marker *marker)
{
	for (int i = 0; i < g_838450; i++) {
		SmsData *d = GetSmsData(i);
		if (d->type == 0xF && d->data.typeAstageIndex == marker->hash)
			return IsMessageAlreadyReceived(d) ? false : true;
	}
	return false;
}
