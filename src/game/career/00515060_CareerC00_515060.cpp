// PROFILE: game
// CareerC00::515060, 105 bytes
// yugecin's prototype: int __thiscall CareerC00__515060(struct CareerC00 *this, struct Career_0 *into);
#include "game/CareerC00.h"
#include "game/Career_0.h"
#include "game/CareerShop.h"

struct CareerC00_8 { unsigned char pad[0xC]; unsigned int hash; };
struct Obj4FFF80 { unsigned char pad[0x2C]; unsigned int markerHash; };
CareerShop *FindCareerShopByHash(unsigned int hash);
Marker *FindMarkerTypeD_E_FWithHash(unsigned int hash);
Obj4FFF80 *sub_4FFF80(unsigned int hash);

// FUNCTION: 0x00515060
void CareerC00::sub_515060(Career_0 *into)
{
	into->field_0 = 0;
	into->field_4 = 0;
	into->careerShop8 = 0;
	into->field_C = 0;
	into->field_10 = 0;
	CareerC00_8 *f = (CareerC00_8 *)field_8;
	if (f) {
		unsigned int hash = f->hash;
		CareerShop *shop = FindCareerShopByHash(hash);
		if (shop) {
			into->careerShop8 = shop;
			into->field_0 = FindMarkerTypeD_E_FWithHash(shop->markerHash);
			return;
		}
		Obj4FFF80 *x = sub_4FFF80(hash);
		if (x) {
			into->field_C = x;
			into->field_0 = FindMarkerTypeD_E_FWithHash(x->markerHash);
		}
	}
}
