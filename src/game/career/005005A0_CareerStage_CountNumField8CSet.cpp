// PROFILE: game
// CareerStage::CountNumField8CSet, 51 bytes
// yugecin's prototype: int __thiscall CareerStage__CountNumField8CSet(struct CareerStage *this);
#include "game/CareerStage.h"

// FUNCTION: 0x005005A0
int CareerStage::CountNumField8CSet()
{
	int n = 0;
	for (int i = 0; i < 4; i++) {
		if (field_8C[i])
			n++;
	}
	return n;
}
