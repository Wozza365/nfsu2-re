// PROFILE: game
// SmsMessageList::GetFirstUnreadSmsMessage, 54 bytes
// yugecin's prototype: struct SmsMessage *__thiscall SmsMessageList__GetFirstUnreadSmsMessage(struct SmsMessageList *this);
#include "game/SmsMessageList.h"

// FUNCTION: 0x00514CF0
SmsMessage *SmsMessageList::GetFirstUnreadSmsMessage()
{
	for (int i = 0; i < numMessages; i++) {
		SmsMessage *sms = GetAtIndex(i);
		if (!sms->read && sms->deleted != 1)
			return sms;
	}
	return 0;
}
