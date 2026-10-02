// PROFILE: game
// NONMATCHING: the game computes the CareerCar434 pointer with one lea after the call; ours
// copies eax and adds 0x434 later (register allocation only).
// Career::HandleMoneyAfterPartBought, 98 bytes
// yugecin's prototype: int __thiscall Career__HandleMoneyAfterPartBought(struct Career *this, int, int);
// yugecin's note: changes {{struct Career.7134}} and {{struct CareerCar434.3BC}} ||| code,ref,code,ref
#include "game/Career.h"
#include "game/CarCollection.h"
#include "game/CareerCar.h"

extern CarCollection g_83AD90;

// FUNCTION: 0x005289F0
void Career::HandleMoneyAfterPartBought(int a1, void *a2)
{
	if (a2) {
		int cost = GetPartCost(a1, a2);
		bank.money -= cost;
		if (bank.money < 0)
			bank.money = 0;
		CareerCar434 *c = &g_83AD90.GetCareerCarForSlotHash(activeCarSlotHash)->field_434;
		c->sub_503D50(a1, (int)a2);
		c->moneySpentOnCar += cost;
	}
}
