// PROFILE: game
// SmsMessageList::IsMessageAlreadyReceived, 60 bytes
// yugecin's prototype: int __thiscall SmsMessageList__IsMessageAlreadyReceived(struct SmsMessageList *this, struct SmsData *smsdata);
#include "game/SmsMessageList.h"
#include "game/SmsMessage.h"

// FUNCTION: 0x00514CB0
bool SmsMessageList::IsMessageAlreadyReceived(SmsData *smsdata)
{
	for (int i = 0; i < numMessages; i++) {
		if (GetAtIndex(i)->data == smsdata)
			return true;
	}
	return false;
}
