// PROFILE: game
// Career::513950, 103 bytes
// yugecin's prototype: int __thiscall Career__513950(struct Career *this);
#include "game/Career.h"

struct C2_4 { char pad[0x60]; vec3 pos; char pad2[0x40C - 0x6C]; unsigned short angle; };
struct C2 { int field_0; C2_4 *field_4; };
extern C2 *g_8900AC;
extern int g_89E7B0;
struct Obj890118 { void sub_5EEE80(); };
extern Obj890118 *g_890118;

// FUNCTION: 0x00513950
void Career::sub_513950()
{
	currentRace_lastRace_ = 0;
	field_D24.field_1 = 0;
	field_8744 = 1;
	if (g_89E7B0 == 7) {
		C2_4 *p = g_8900AC->field_4;
		if (p) {
			float x = p->pos.x;
			float y = p->pos.y;
			float z = p->pos.z;
			carPosition.x = x;
			carPosition.y = y;
			carPosition.z = z;
			carAngle = p->angle;
		}
	}
	if (g_890118)
		g_890118->sub_5EEE80();
}
