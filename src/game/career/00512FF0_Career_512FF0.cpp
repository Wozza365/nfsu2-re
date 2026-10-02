// PROFILE: game
// Career::512FF0, 91 bytes
// yugecin's prototype: int __thiscall Career__512FF0(struct Career *this, struct Marker *marker, struct CareerShop *shop);
#include "game/Career.h"
#include "game/CareerShop.h"

void sub_4ECCF0(Career_0 *a1);

// FUNCTION: 0x00512FF0
void Career::sub_512FF0(Marker *marker, CareerShop *shop)
{
	if (shop->stageIndex > currentStage)
		return;
	unsigned int hash = shop->hash;
	Career7B00 *e = FindCareer7B00WithHash0(hash);
	if (!e)
		e = sub_512F10(hash);
	if (!e->field_4 && shop->isHiddenShop)
		sub_4ECCF0(sub_500E20(marker, shop));
	e->field_4 = 1;
}
