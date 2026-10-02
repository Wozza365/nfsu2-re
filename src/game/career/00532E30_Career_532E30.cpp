// PROFILE: game
// Career::532E30, 26 bytes
// yugecin's prototype: void __thiscall Career__532E30(struct Career *this);
// yugecin's note: calls {529B50} and {511000} ||| ref,ref
#include "game/Career.h"

// FUNCTION: 0x00532E30
void Career::sub_532E30()
{
	smsMessageList.SendOutrunInfoSms();
	field_887C.sub_511000();
}
