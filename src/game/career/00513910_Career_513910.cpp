// PROFILE: game
// Career::513910, 50 bytes
// yugecin's prototype: void *__thiscall Career__513910(struct Career *this);
#include "game/Career.h"

extern void *g_838458;
unsigned int cshash(char *str);
CareerShop *FindCareerShopByHash(unsigned int hash);

// FUNCTION: 0x00513910
void *Career::sub_513910()
{
	if (field_C00.field_11C == 4) {
		if (!g_838458)
			g_838458 = FindCareerShopByHash(cshash("THE_UNIQUES_SHOP"));
		return g_838458;
	}
	return field_8734;
}
