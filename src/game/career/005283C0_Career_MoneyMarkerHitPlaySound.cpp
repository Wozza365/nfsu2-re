// PROFILE: game
// Career::MoneyMarkerHitPlaySound??, 76 bytes
// yugecin's prototype: void __thiscall Career__MoneyMarkerHitPlaySound__(struct Career *this, struct Marker *marker);
// yugecin's note: param marker may be null  this func only plays some sound!?
#include "game/Career.h"

struct Marker { unsigned char pad[0x30]; unsigned int hash; };
struct Bin34A1E { unsigned int field_0; unsigned int field_4; unsigned int hash; };
extern Bin34A1E *g_838430;
extern int g_838434;

// FUNCTION: 0x005283C0
void Career::MoneyMarkerHitPlaySound(Marker *marker)
{
	if (marker) {
		unsigned int hash = marker->hash;
		for (int i = 0; i < g_838434; i++) {
			Bin34A1E *e = &g_838430[i];
			if (e->hash == hash) {
				if (sub_513890(e))
					PlaySound528370(e);
				return;
			}
		}
	}
}
