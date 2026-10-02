// PROFILE: game
// Career4230::500D20, 74 bytes
// yugecin's prototype: int __thiscall Career4230__500D20(struct Career4230 *this, int);
#include "game/Career4230.h"

struct Obj9A4 { void sub_4DB890(int a1); };
struct C2 { unsigned char pad[0x9A4]; Obj9A4 *field_9A4; };
extern C2 *g_8900AC;

// FUNCTION: 0x00500D20
void Career4230::sub_500D20(int a1)
{
	if (!a1) {
		g_8900AC->field_9A4->sub_4DB890(a1);
		field_1AE8 = 3;
	} else {
		g_8900AC->field_9A4->sub_4DB890(a1);
		field_1AE8 = 2;
	}
}
