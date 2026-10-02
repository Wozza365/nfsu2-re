// PROFILE: game
// Career::54C940 (131 bytes), Career::54C9D0 (90 bytes), Career::j_54C940 (54CA30, 5 bytes),
// Career::54CA60 (117 bytes)
// One file: neighbours in the exe, and 54C9D0 relies on what 54C940 does with registers.
// Career::54C940 (131 bytes), Career::54C9D0 (90 bytes), Career::j_54C940 (54CA30, 5 bytes),
// Career::54CA60 (117 bytes)
// One file: neighbours in the exe, and 54C9D0 relies on what 54C940 does with registers.
#include "game/Career.h"
#include "game/CareerD24_54.h"
#include "game/CareerRace.h"

extern CareerD24_54_30 g_85036C;
struct Obj890118 { void sub_5EEE80(); };
extern Obj890118 *g_890118;

// FUNCTION: 0x0054C940
void Career::sub_54C940()
{
	if (field_D24.field_1 && !field_D24.field_4) {
		CareerD24 *d24 = &field_D24;
		CareerD24_54 *d = d24->ptrCareerDataD24_54;
		if (d->field_14 == 3) {
			d->field_14 = 4;
			d->field_30.CopyFrom(&g_85036C);
		}
		if (d24->sub_5287A0(1))
			d24->field_4 = 1;
		if (d24->sub_5287A0(1))
			DoPostRaceThings(currentRace_lastRace_->hash);
		else
			sub_528500(currentRace_lastRace_->hash);
	}
}

// FUNCTION: 0x0054C9D0
bool Career::sub_54C9D0(char *movieNameBuffer)
{
	int raceStage = currentRace_lastRace_->stageIndex;
	sub_54C940();
	int stage = currentStage;
	bool result = GetMovieNameToPlay(raceStage != stage, movieNameBuffer);
	currentRace_lastRace_ = 0;
	field_D24.field_1 = 0;
	field_8744 = 1;
	if (g_890118)
		g_890118->sub_5EEE80();
	return result;
}

// FUNCTION: 0x0054CA30
void Career::j_54C940()
{
	sub_54C940();
}

// NONMATCHING (54CA60, 80%): the shape of the second field_1 check and the d24 pointer isn't right yet.
// FUNCTION: 0x0054CA60
void Career::sub_54CA60(int)
{
	if (field_D24.field_1 && currentRace_lastRace_) {
		CareerD24 *d24 = &field_D24;
		if (field_D24.field_1) {
			CareerD24_54 *d = d24->ptrCareerDataD24_54;
			d->field_14 = 3;
			d->field_30.CopyFrom(&g_85036C);
		}
		if (d24->sub_5287A0(0) && currentRace_lastRace_)
			stages[currentRace_lastRace_->stageIndex].sub_513390(currentRace_lastRace_);
	}
}
