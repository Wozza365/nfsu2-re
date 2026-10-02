// PROFILE: game
// MenuCarInstance_10_2E0::5A6400, 72 bytes
// yugecin's prototype: int __thiscall MenuCarInstance_10_2E0__5A6400(struct MenuCarInstance_10_2E0 *this, struct Bin34A15 *bin34A15, int);
#include "game/MenuCarInstance_10_2E0.h"

struct Bin34A15_C { unsigned char data[0x5C]; };
struct Bin34A15 {
	unsigned int field_0;
	unsigned int field_4;
	unsigned int numEntriesInFieldC;
	Bin34A15_C field_C[3];
};

// FUNCTION: 0x005A6400
int MenuCarInstance_10_2E0::sub_5A6400(Bin34A15 *bin34A15, int a2)
{
	int total = 0;
	for (unsigned int i = 0; i < bin34A15->numEntriesInFieldC; i++)
		total += sub_5A6320(&bin34A15->field_C[i], a2, 0);
	return total;
}
