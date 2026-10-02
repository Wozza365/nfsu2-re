// PROFILE: game
// Career::ShouldShowShopOnMap, 79 bytes
// yugecin's prototype: int __thiscall Career__ShouldShowShopOnMap(struct Career *this, struct CareerShop *shop);
#include "game/Career.h"
#include "game/CareerShop.h"

extern bool g_838441;  // showAllHiddenShops

// FUNCTION: 0x00513110
bool Career::ShouldShowShopOnMap(CareerShop *shop)
{
	if (g_838441)
		return true;
	if (shop->stageIndex > currentStage)
		return false;
	if (shop->isHiddenShop) {
		Career7B00 *e = FindCareer7B00WithHash0(shop->hash);
		if (!e || e->field_4 != 1)
			return false;
	}
	return shop->IsExtraMapVisibilityConditionFulfilled();
}
