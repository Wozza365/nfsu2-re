// PROFILE: game
// NONMATCHING: belongs with 514CB0 (see src/game/zSms.cpp), but the register allocation still
// differs: the game keeps the count in ebx and this on the stack.
// SmsMessageList::SendOutrunVictoryOrDefeatSms, 110 bytes
// yugecin's prototype: void __thiscall SmsMessageList__SendOutrunVictoryOrDefeatSms(struct SmsMessageList *this, int didWin);
// yugecin's note: Goes through all {838454}. When {didWin} is 1, send all with {{struct SmsData+2} == {enum SMS_TYPE/0x5}}, else send ||| ref,code,code,ref,ref all with {{struct SmsData+2} == {enum SMS_TYPE/0x6}}. Uses
#include "game/SmsMessageList.h"
#include "game/SmsData.h"

extern SmsData *g_838454;  // smsDatas
extern int g_838450;  // numSmsDatas

static inline SmsData *GetSmsData(int i)
{
	if (i >= 0 && i < g_838450)
		return &g_838454[i];
	return 0;
}

// FUNCTION: 0x00529BD0
void SmsMessageList::SendOutrunVictoryOrDefeatSms(bool didWin)
{
	for (int i = 0; i < g_838450; i++) {
		SmsData *d = GetSmsData(i);
		if ((didWin && d->type == 5) || (!didWin && d->type == 6)) {
			if (!IsMessageAlreadyReceived(d))
				SendMessage(d);
		}
	}
}
