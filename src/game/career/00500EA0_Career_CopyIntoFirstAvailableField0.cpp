// PROFILE: game
// Career::CopyIntoFirstAvailableField0, 61 bytes
// yugecin's prototype: void __thiscall Career__CopyIntoFirstAvailableField0(struct Career *this, struct Career_0 *from);
#include <string.h>
#include "game/Career.h"

// NONMATCHING (62%): everything matches except the 24-byte copy: the game uses rep movsd (ecx=6),
// our compiler unrolls it into six moves, both for memcpy and for struct assignment. /Os gives
// rep movsd but changes everything else.
// FUNCTION: 0x00500EA0
Career_0 *Career::CopyIntoFirstAvailableField0(Career_0 *from)
{
	Career_0 *entry = FindFreeField0();
	if (entry) {
		memcpy(entry, from, sizeof(Career_0));
		entry->field_14 = 0;
	}
	return entry;
}
