// PROFILE: game
// NONMATCHING: the game interleaves the zero stores to field_C/10/14 with the pushes for the first
// vector constructor call; ours stores them after the pushes. Body assignments instead of the
// initializer list are further off.
// CareerD24_54_30::ctor, 87 bytes
// yugecin's prototype: struct CareerD24_54_30 *__thiscall CareerD24_54_30__ctor(struct CareerD24_54_30 *this);
#include "game/CareerD24_54_30.h"

// FUNCTION: 0x005117C0
CareerD24_54_30::CareerD24_54_30()
{
}
