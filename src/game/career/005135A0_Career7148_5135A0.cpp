// PROFILE: game
// Career7148::5135A0, 83 bytes
// yugecin's prototype: int __thiscall Career7148__5135A0(struct Career7148 *this, __int16 *ptrOffsetInCareerStringPool);
#include "game/Career7148.h"

extern char *g_838428;  // careerStringPool

// FUNCTION: 0x005135A0
bool Career7148::sub_5135A0(unsigned short *ptrOffsetInCareerStringPool)
{
	for (int i = 0; i < 32; i++) {
		unsigned short *e = field_0[i];
		if (e) {
			unsigned int hash = cshash(g_838428 + *ptrOffsetInCareerStringPool);
			if (cshash(g_838428 + *e) == hash)
				return true;
		}
	}
	return false;
}
