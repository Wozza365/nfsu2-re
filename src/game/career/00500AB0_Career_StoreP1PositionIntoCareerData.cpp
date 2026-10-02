// PROFILE: game
// Career::StoreP1PositionIntoCareerData, 65 bytes
// yugecin's prototype: void __thiscall Career__StoreP1PositionIntoCareerData(struct Career *this, int unused);
// yugecin's note: writes to {struct Career.8750} and {struct Career.8760} ||| ref,ref
#include "game/Career.h"

struct C2_4 { char pad[0x60]; vec3 pos; char pad2[0x40C - 0x6C]; unsigned short angle; };
struct C2 { int field_0; C2_4 *field_4; };
extern C2 *g_8900AC;

// FUNCTION: 0x00500AB0
void Career::StoreP1PositionIntoCareerData(int)
{
	if (g_8900AC) {
		C2_4 *p = g_8900AC->field_4;
		field_8744 = 1;
		float x = p->pos.x;
		float y = p->pos.y;
		float z = p->pos.z;
		carPosition.x = x;
		carPosition.y = y;
		carPosition.z = z;
		carAngle = p->angle;
	}
}
