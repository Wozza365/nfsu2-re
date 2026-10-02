// PROFILE: game
// Career::5142E0, 90 bytes
// yugecin's prototype: int __thiscall Career__5142E0(struct Career *this, int, int, int);
#include "game/Career.h"
#include "game/Car.h"

struct Part5142E0 {
	unsigned short lo;
	unsigned short hi;
	unsigned char field_4;
	unsigned char field_5;
};
int sub_501D70(int a1, void *a2);
int sub_501860(int a1, int a2);
extern Car *g_8A1CCC;  // ptrCarData

// FUNCTION: 0x005142E0
int Career::sub_5142E0(int a1, int a2, void *a3)
{
	Part5142E0 *p = (Part5142E0 *)a3;
	int x = sub_501D70(a2, a3);
	int r = sub_501860(x, (char)(p->field_5 >> 5));
	if ((a2 == 0x3F && ((p->hi << 16) | p->lo) == g_8A1CCC[a1].field_84C) || r == -1)
		return 0;
	return r;
}
