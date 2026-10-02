// PROFILE: game
// Career4230::500CB0, 56 bytes
// yugecin's prototype: int __thiscall Career4230__500CB0(struct Career4230 *this);
#include "game/Career4230.h"

extern int g_850078;
extern int g_862838;
extern bool g_86347E;

// FUNCTION: 0x00500CB0
bool Career4230::sub_500CB0()
{
	if (g_850078 == 1 && g_862838 == 0 && g_86347E)
		return false;
	return field_1AE8 == 1;
}
