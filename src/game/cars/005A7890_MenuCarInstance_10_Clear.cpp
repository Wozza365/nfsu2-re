// PROFILE: game
// NONMATCHING: the game computes &field_30 before the store to field_374.field_8; here it comes
// after (scheduling only). Inline helpers, a reference and a temporary did not change it.
// MenuCarInstance_10::Clear, 77 bytes
// yugecin's prototype: void __thiscall MenuCarInstance_10__Clear(struct MenuCarInstance_10 *this, int);
#include "game/MenuCarInstance_10.h"

// FUNCTION: 0x005A7890
void MenuCarInstance_10::Clear(int a1)
{
	field_0 = a1;
	field_4 = 0xFF;
	field_8 = 0;
	field_10 = 0;
	field_14 = 0;
	field_18 = 0;
	field_20 = 0;
	field_1C = 0;
	field_2E0.sub_5A6450(-1);
	field_374.field_8 = &field_2E0;
	field_374.field_0 = a1;
	field_374.field_C = &field_30;
}
