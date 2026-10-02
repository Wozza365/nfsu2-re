// PROFILE: game
// Career::IsInCareerAndTotallyFreeroaming??, 28 bytes
// yugecin's prototype: int __thiscall Career__IsInCareerAndTotallyFreeroaming__(struct Career *this);
// yugecin's note: is doing pure freeroam stuff in career I guess
#include "game/Career.h"

extern int g_850078;
extern int g_89E7B0;

// FUNCTION: 0x00500B60
int Career::IsInCareerAndTotallyFreeroaming()
{
	return g_850078 == 1 && g_89E7B0 == 0;
}
