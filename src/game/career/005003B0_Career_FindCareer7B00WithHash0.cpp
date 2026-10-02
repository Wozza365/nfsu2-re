// PROFILE: game
// Career::FindCareer7B00WithHash0, 59 bytes
// An ordinary function: functions after it in the same jumbo file inline it (512F10, 500460, ...) or
// call it knowing it leaves ecx alone (512FF0). See src/game/zCareer.cpp.
#include "game/Career.h"
#include "game/Career7B00.h"

// FUNCTION: 0x005003B0
Career7B00 *Career::FindCareer7B00WithHash0(unsigned int hash)
{
	for (int i = 0; i < numUsed7B00; i++) {
		if (field_7B00[i].hash == hash)
			return &field_7B00[i];
	}
	return 0;
}
