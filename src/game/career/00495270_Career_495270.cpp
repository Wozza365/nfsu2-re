// PROFILE: game
// Career::495270, 20 bytes
// yugecin's prototype: int __thiscall Career__495270(struct Career *this);
// yugecin's note: {return this->{struct Career+8704} ? this->{struct Career+8710} : 0;} ||| code,ref,ref
#include "game/Career.h"

// FUNCTION: 0x00495270
int Career::sub_495270()
{
	return field_8704 ? field_8710 : 0;
}
