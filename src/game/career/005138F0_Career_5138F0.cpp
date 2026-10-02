// PROFILE: game
// Career::5138F0, 20 bytes
// yugecin's prototype: int __thiscall Career__5138F0(struct Career *this, void *);
#include "game/Career.h"
#include "game/Career7B00.h"

// FUNCTION: 0x005138F0
void Career::sub_5138F0(void *a1)
{
	Career7B00 *entry = sub_512F10(((unsigned int *) a1)[2]);
	entry->field_6 = 3;
}
