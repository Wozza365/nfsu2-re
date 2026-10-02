// PROFILE: game
// MenuCarInstance_10_2E0::599680, 48 bytes
// yugecin's prototype: int __thiscall MenuCarInstance_10_2E0__599680(struct MenuCarInstance_10_2E0 *this, int index, int, int);
#include "game/MenuCarInstance_10_2E0.h"

Bin34A15_C *GetBin34A15_CAtIndex(int index);

// FUNCTION: 0x00599680
int MenuCarInstance_10_2E0::sub_599680(int index, int a2, int a3)
{
	Bin34A15_C *bin = GetBin34A15_CAtIndex(index);
	if (bin)
		return sub_5A6320(bin, a2, a3);
	return 0;
}
