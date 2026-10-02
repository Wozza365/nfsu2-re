// PROFILE: game
// SmsMessageList::SendMessageByHash, 48 bytes
// yugecin's prototype: struct SmsMessage *__thiscall SmsMessageList__SendMessageByHash(struct SmsMessageList *this, int hash);
// yugecin's note: Combines {501310}, {514CB0} and {5295F0}. ||| ref,ref,ref
#include "game/SmsMessageList.h"

SmsData *GetSmsDataForHash(unsigned int hash);

// FUNCTION: 0x00533890
void SmsMessageList::SendMessageByHash(int hash)
{
	SmsData *data = GetSmsDataForHash(hash);
	if (data && !IsMessageAlreadyReceived(data))
		SendMessage(data);
}
