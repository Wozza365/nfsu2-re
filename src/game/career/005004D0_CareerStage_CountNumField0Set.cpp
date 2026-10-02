// PROFILE: game
// CareerStage::CountNumField0Set, 78 bytes
// yugecin's prototype: int __thiscall CareerStage__CountNumField0Set(struct CareerStage *this);
#include "game/CareerStage.h"

// FUNCTION: 0x005004D0
int CareerStage::CountNumField0Set()
{
	int count = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			if (field_0[i][j])
				count++;
		}
	}
	return count;
}
