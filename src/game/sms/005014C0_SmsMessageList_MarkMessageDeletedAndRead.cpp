// PROFILE: game
// SmsMessageList::MarkMessageDeletedAndRead, 45 bytes
// yugecin's prototype: void __thiscall SmsMessageList__MarkMessageDeletedAndRead(struct SmsMessageList *this, struct SmsMessage *sms);
// yugecin's note: .controlchars [] .pushmode pre if (!sms->[struct SmsMessage+6] && !sms->[struct SmsMessage+4]) { ||| ref,ref       this->[struct SmsMessageList+1404]--; ||| ref } sms->[struct SmsMessage+6] = 1; ||| r
#include "game/SmsMessageList.h"

// FUNCTION: 0x005014C0
void SmsMessageList::MarkMessageDeletedAndRead(SmsMessage *sms)
{
	bool wasRead = sms->deleted == 1 || sms->read == 1;
	sms->deleted = 1;
	if (!wasRead)
		numUnreadMessages--;
	sms->read = 1;
}
