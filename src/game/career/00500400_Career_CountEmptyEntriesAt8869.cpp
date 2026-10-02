// PROFILE: game
// Career::CountEmptyEntriesAt8869, 86 bytes
// yugecin's prototype: int __thiscall Career__CountEmptyEntriesAt8869(struct Career *this);
// yugecin's note: {struct Career+8869} is {char[8][2]}, this counts how many of those 16 fields are set to 0 ||| ref,code
#include "game/Career.h"

// FUNCTION: 0x00500400
int Career::CountEmptyEntriesAt8869()
{
	int count = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			if (!field_8869[i][j])
				count++;
		}
	}
	return count;
}
