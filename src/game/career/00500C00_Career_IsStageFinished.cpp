// PROFILE: game
// Career::IsStageFinished?, 46 bytes
// yugecin's prototype: int __thiscall Career__IsStageFinished_(struct Career *this, int stageIndex);
// yugecin's note: {return this->{struct Career+72D8}[arg0].{struct CareerStage+FC}} ||| code,ref,ref  crash if arg0 < 0 or > 7
#include "game/Career.h"

// FUNCTION: 0x00500C00
bool Career::IsStageFinished(int stageIndex)
{
	return GetStage(stageIndex)->stageFinished_;
}
