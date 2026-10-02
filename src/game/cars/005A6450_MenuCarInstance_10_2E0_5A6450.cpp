// PROFILE: game
// MenuCarInstance_10_2E0::5A6450, 76 bytes
// yugecin's prototype: int __thiscall MenuCarInstance_10_2E0__5A6450(struct MenuCarInstance_10_2E0 *this, int);
#include "game/MenuCarInstance_10_2E0.h"

struct Bin34A15 { int field_0; };
int GetNumBin34A15();
Bin34A15 *GetBin34A15AtIndex(int index);

// FUNCTION: 0x005A6450
int MenuCarInstance_10_2E0::sub_5A6450(int a1)
{
	int total = 0;
	for (int i = 0; i < GetNumBin34A15(); i++) {
		Bin34A15 *b = GetBin34A15AtIndex(i);
		if (b && (a1 == -1 || a1 == b->field_0))
			total += sub_5A6400(b, 0);
	}
	return total;
}
