// PROFILE: game
// SmsMessageList::GetAtIndex, 30 bytes
// yugecin's prototype: struct SmsMessage *__thiscall SmsMessageList__GetAtIndex(struct SmsMessageList *this, int index);
// yugecin's note: TODO: check xrefs
#include "game/SmsMessageList.h"

// GetAtIndex is defined inline in SmsMessageList.h, as in the game, where its callers inline it.
// Taking its address makes the compiler emit the out-of-line copy the game also has.
// FUNCTION: 0x005014A0 SYMBOL=?GetAtIndex@SmsMessageList@@QAEPAUSmsMessage@@H@Z
typedef SmsMessage *(SmsMessageList::*GetAtIndexFn)(int);
GetAtIndexFn emit_GetAtIndex() { return &SmsMessageList::GetAtIndex; }
