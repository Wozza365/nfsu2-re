// PROFILE: game
// NONMATCHING: the game keeps this on the stack and never uses ebp; ours puts this in ebp.
// Otherwise identical (in src/game/zCareer.cpp, which it needs for the count kept in ebx).
// CareerStage::513490, 113 bytes
// yugecin's prototype: int __thiscall CareerStage__513490(struct CareerStage *this);
#include "game/CareerStage.h"
#include "game/CareerStageSettings.h"
#include "game/Career.h"

struct Bin34A16 {
	unsigned char pad_0[0x20];
	unsigned int hash;
	unsigned char pad_24;
	unsigned char stageIndex;
	unsigned char pad_26[0xF];
	unsigned char field_35;
	unsigned char pad_36[0xA];
};
extern Bin34A16 *g_83840C;  // bin34A16
extern int g_838408;  // numBin34A16

static inline Bin34A16 *GetBin34A16(int i)
{
	if (i >= 0 && i < g_838408)
		return &g_83840C[i];
	return 0;
}

// FUNCTION: 0x00513490
bool CareerStage::sub_513490()
{
	for (int i = 0; i < g_838408; i++) {
		Bin34A16 *b = GetBin34A16(i);
		if (b && b->stageIndex == settings->stageIndex && b->field_35 && !g_85AD40.sub_500B80(b->hash))
			return false;
	}
	return true;
}
