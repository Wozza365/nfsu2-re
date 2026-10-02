// PROFILE: game
// Career::5278F0, 119 bytes
// yugecin's prototype: int __thiscall Career__5278F0(struct Career *this);
#include "game/Career.h"

// FUNCTION: 0x005278F0
bool Career::sub_5278F0()
{
	if (field_7138)
		return false;
	if (someCareerShop8724 && ShouldShowShopOnMap(someCareerShop8724))
		return true;
	if (field_871C && field_7148.HasSomething5007E0(field_871C))
		return true;
	if (field_8728 && field_4210.sub_501150(field_8728))
		return true;
	if (field_8720 && field_7148.sub_5135A0(field_8720))
		return true;
	return false;
}
