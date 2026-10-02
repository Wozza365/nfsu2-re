// PROFILE: game
// NONMATCHING: same memset setup order difference as Career887C::ctor (512EB0): the game loads edi
// first ("lea edi / mov ecx / xor eax"), ours last. The rest matches, including the inlined
// MenuCarInstance_10_2E0 constructor.
// TunedCar18::ctor, 86 bytes
// yugecin's prototype: void __thiscall TunedCar18__ctor(struct TunedCar18 *this);
#include "game/TunedCar18.h"

// FUNCTION: 0x00516A60
TunedCar18::TunedCar18()
{
	field_0 = 0;
}
