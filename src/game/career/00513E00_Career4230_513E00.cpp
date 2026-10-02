// PROFILE: game
// Career4230::513E00, 45 bytes
// yugecin's prototype: int __thiscall Career4230__513E00(struct Career4230 *this, int);
#include "game/Career4230.h"

extern int g_850078;
extern int g_862838;
extern bool g_86347E;
extern int g_85B948;

// FUNCTION: 0x00513E00
bool Career4230::sub_513E00(int a1)
{
	if (g_850078 == 1 && g_862838 == 0 && g_86347E)
		return false;
	if (g_85B948)
		return false;
	return true;
}
