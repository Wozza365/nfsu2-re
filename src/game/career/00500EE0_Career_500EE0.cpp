// PROFILE: game
// NONMATCHING: for a null prev the game jumps straight into the loop (edx is already 0); here it
// goes through the shared "i = 0" block first. Only that branch target differs.
// Career::500EE0, 80 bytes
// yugecin's prototype: int __thiscall Career__500EE0(struct Career *this, int);
#include "game/Career.h"

extern int g_850078;

// FUNCTION: 0x00500EE0
Career_0 *Career::sub_500EE0(Career_0 *prev)
{
	if (g_850078 != 1)
		return 0;
	int i;
	if (prev) {
		i = ((char *)prev - (char *)field_0) / sizeof(Career_0) + 1;
		if (i < 0)
			i = 0;
	} else {
		i = 0;
	}
	for (; i < 64; i++) {
		if (field_0[i].field_0)
			return &field_0[i];
	}
	return 0;
}
