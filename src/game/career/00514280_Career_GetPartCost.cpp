// PROFILE: game
// Career::GetPartCost, 96 bytes
// yugecin's prototype: int __thiscall Career__GetPartCost(struct Career *this, int, int);
// Career::GetPartCost, 96 bytes
// yugecin's prototype: int __thiscall Career__GetPartCost(struct Career *this, int, int);
#include "game/Career.h"

struct Part514280 {
	unsigned short lo;
	unsigned short hi;
	unsigned char field_4;
	unsigned char field_5;
};
struct Bin34A1C_Cost { short field_0; short cost; };
struct Bin34A1C {
	unsigned char data[0x28];
	Bin34A1C_Cost *sub_501750(int kind);
};
extern Bin34A1C *g_83845C;  // bin34A1C
int sub_501D70(int a1, void *a2);

static inline Bin34A1C *GetBin34A1C(int index)
{
	if (index > 0 && index < 0x57)
		return &g_83845C[index - 1];
	return 0;
}

// FUNCTION: 0x00514280
int Career::GetPartCost(int a1, void *a2)
{
	Part514280 *p = (Part514280 *)a2;
	int x = sub_501D70(a1, a2);
	int kind = (char)(p->field_5 >> 5);
	if (kind == 4)
		return 0;
	if (kind == 0) {
		if (x != 0x4C)
			return 0;
		kind = 1;
	}
	Bin34A1C *b = GetBin34A1C(x);
	if (b) {
		int cost = b->sub_501750(kind)->cost;
		if (cost != -1)
			return cost;
	}
	return 0;
}
