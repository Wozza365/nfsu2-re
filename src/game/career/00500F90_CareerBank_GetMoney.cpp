// PROFILE: game
// CareerBank::GetMoney, 3 bytes
// yugecin's prototype: int __thiscall CareerBank__GetMoney(struct CareerBank *this);
// yugecin's note: Only used in career money cheats, and to show bank label in career freeroam? not for pchelpbar, other transactions etc...
#include "game/CareerBank.h"

// FUNCTION: 0x00500F90
int CareerBank::GetMoney()
{
	return money;
}
