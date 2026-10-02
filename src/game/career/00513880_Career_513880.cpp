// PROFILE: game
// Career::513880, 16 bytes
// yugecin's prototype: int __thiscall Career__513880(struct Career *this);
// yugecin's note: check if something is collected
#include "game/Career.h"
#include "game/CareerStageSettings.h"

// FUNCTION: 0x00513880
bool Career::sub_513880()
{
	return sub_500B80(stages[5].settings->field_28);
}
