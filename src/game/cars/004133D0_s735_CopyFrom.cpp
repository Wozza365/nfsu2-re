// PROFILE: game
// NONMATCHING: the game builds the s735_100 in a stack temporary and copies it with rep movsd;
// ours stores the fields directly (the open struct-copy question, as in 500EA0). The loop has
// ecx/eax swapped. /Os and /O1 do not give rep movsd here either.
// s735::CopyFrom, 104 bytes
// yugecin's prototype: void __thiscall s735__CopyFrom(struct s735 *this, struct s735 *from);
// s735::CopyFrom, 104 bytes
// yugecin's prototype: void __thiscall s735__CopyFrom(struct s735 *this, struct s735 *from);
// yugecin's note: not an exact copy
#include "game/s735.h"

// FUNCTION: 0x004133D0
void s735::CopyFrom(s735 *from)
{
	int i = 0;
	do {
		floatField_0[i] = from->floatField_0[i];
		i++;
	} while (i < 63);
	field_100 = s735_100(0x40, from->field_100.floatField_4, from->field_100.floatField_8, this);
}
