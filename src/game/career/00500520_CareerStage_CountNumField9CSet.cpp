// PROFILE: game
// CareerStage::CountNumField9CSet, 117 bytes
// yugecin's prototype: int __thiscall CareerStage__CountNumField9CSet(struct CareerStage *this);
#include "game/CareerStage.h"

// FUNCTION: 0x00500520
int CareerStage::CountNumField9CSet()
{
	int count = 0;
	for (int i = 0; i < 10; i++) {
		if (field_9C[i])
			count++;
	}
	return count;
}
