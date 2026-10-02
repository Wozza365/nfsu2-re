// PROFILE: game
// CareerBank::AddMoney, 13 bytes
// yugecin's prototype: void __thiscall CareerBank__AddMoney(struct CareerBank *this, int amount);
// yugecin's note: Only used in the career money cheats.
#include "game/CareerBank.h"

// FUNCTION: 0x00500F80
void CareerBank::AddMoney(int amount)
{
	money += amount;
}
