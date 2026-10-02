// PROFILE: game
// SmsMessage::GetSenderLanguageHash, 6 bytes
// yugecin's prototype: unsigned int __thiscall SmsMessage__GetSenderLanguageHash(struct SmsMessage *this);
// yugecin's note: Returns the hash for the language string that is the sms sender. Used once in {497850}. ||| ref  .pushmode pre return this->{struct SmsMessage+0}.{struct SmsData+10}; ||| ref,ref .popmode pre
#include "game/SmsMessage.h"
#include "game/SmsData.h"

// FUNCTION: 0x00501470
unsigned int SmsMessage::GetSenderLanguageHash()
{
	return data->senderLanguageLabel;
}
