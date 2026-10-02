// PROFILE: game
// SmsMessageList::GetNumUnreadMessages, 75 bytes
// yugecin's prototype: int __thiscall SmsMessageList__GetNumUnreadMessages(struct SmsMessageList *this, int useCachedFlag);
// yugecin's note: When {useCachedFlag}, just return {{83A9D0.20370.5D20.1404}}, otherwise count all ||| code,code,ref {{83A9D0.20370.5D20.0}} that have both {{struct SmsMessage+4}} and ||| code,ref,code,ref {{struct Sm
#include "game/SmsMessageList.h"
#include "game/SmsMessage.h"

// FUNCTION: 0x00514D30
int SmsMessageList::GetNumUnreadMessages(bool useCachedFlag)
{
	if (useCachedFlag)
		return numUnreadMessages;
	int count = 0;
	for (int i = 0; i < numMessages; i++) {
		SmsMessage *m = GetAtIndex(i);
		if (!m->read && m->deleted != 1)
			count++;
	}
	return count;
}
