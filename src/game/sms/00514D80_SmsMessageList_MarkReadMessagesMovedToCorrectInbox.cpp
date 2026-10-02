// PROFILE: game
// SmsMessageList::MarkReadMessagesMovedToCorrectInbox, 57 bytes
// yugecin's prototype: void __thiscall SmsMessageList__MarkReadMessagesMovedToCorrectInbox(struct SmsMessageList *this);
// yugecin's note: For every message, set flag {{struct SmsMessage+7}} when flag {{struct SmsMessage+4}} is set. ||| code,ref,code,ref
#include "game/SmsMessageList.h"

// FUNCTION: 0x00514D80
void SmsMessageList::MarkReadMessagesMovedToCorrectInbox()
{
	for (int i = 0; i < numMessages; i++) {
		SmsMessage *sms = GetAtIndex(i);
		if (sms->read == 1)
			sms->movedToCorrectInbox = 1;
	}
}
