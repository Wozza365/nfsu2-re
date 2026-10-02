// PROFILE: game
// Career::495290, 20 bytes
// yugecin's prototype: int __thiscall Career__495290(struct Career *this);
// yugecin's note: {return this->{struct Career+8704} ? this->{struct Career+8714} : 0;} ||| code,ref,ref
#include "game/Career.h"

// FUNCTION: 0x00495290
int Career::sub_495290()
{
	return field_8704 ? field_8714 : 0;
}
