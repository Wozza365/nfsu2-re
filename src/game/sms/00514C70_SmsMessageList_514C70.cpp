// PROFILE: game
// SmsMessageList::514C70, 61 bytes
// yugecin's prototype: int __thiscall SmsMessageList__514C70(struct SmsMessageList *this);
#include "game/SmsMessageList.h"
#include "game/SmsData.h"

// FUNCTION: 0x00514C70
void SmsMessageList::sub_514C70()
{
	for (int i = 0; i < numMessages; i++) {
		SmsMessage *sms = GetAtIndex(i);
		if (sms->data->field_4 == 1)
			sms->field_5 = 1;
	}
}
