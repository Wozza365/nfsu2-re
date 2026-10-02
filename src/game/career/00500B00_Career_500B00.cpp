// PROFILE: game
// Career::500B00, 61 bytes
// yugecin's prototype: void __thiscall Career__500B00(struct Career *this);
// yugecin's note: .pushmode pre this->{struct Career+8704} = this->{struct Career+8700}; ||| ref,ref this->{struct Career+8708} = this->{struct Career+871C}; ||| ref,ref this->{struct Career+870C} = this->{struct Caree
#include "game/Career.h"

// FUNCTION: 0x00500B00
void Career::sub_500B00()
{
	field_8704 = (void *) field_8700;
	field_8708 = field_871C;
	someCareerShop870C = someCareerShop8724;
	field_8710 = field_8728;
	field_8714 = field_8720;
}
