// PROFILE: game
// Career::532E10, 26 bytes
// yugecin's prototype: int __thiscall Career__532E10(struct Career *this);
#include "game/Career.h"

unsigned int cshash(char *str);

// FUNCTION: 0x00532E10
int Career::sub_532E10()
{
	return sub_532D80(cshash("DDAY_EVENT_B"));
}
