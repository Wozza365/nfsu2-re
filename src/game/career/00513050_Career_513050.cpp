// PROFILE: game
// Career::513050, 77 bytes
// yugecin's prototype: void __thiscall Career__513050(struct Career *this, struct MarkerQueryResult *markerQueryResult);
#include "game/Career.h"

struct Bin34A16 { unsigned char pad[0x20]; unsigned int hash; };
struct MarkerQueryResult {
	Marker *marker;
	CareerRace *foundRace;
	CareerShop *foundShop;
	Bin34A16 *found34A16;
};

// FUNCTION: 0x00513050
void Career::sub_513050(MarkerQueryResult *markerQueryResult)
{
	field_8700 = 0;
	field_871C = 0;
	someCareerShop8724 = 0;
	field_8728 = 0;
	field_8720 = 0;
	if (markerQueryResult->marker && markerQueryResult->found34A16 && field_4210.field_6
		&& field_4210.field_8 == markerQueryResult->found34A16->hash)
		field_4210.field_6 = 0;
}
