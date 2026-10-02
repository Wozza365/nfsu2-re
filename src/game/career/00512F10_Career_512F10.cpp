// PROFILE: game
// Career::512F10: find the 7B00 entry for a hash, or add one
#include "game/Career.h"
#include "game/Career7B00.h"

// FUNCTION: 0x00512F10
Career7B00 *Career::sub_512F10(unsigned int hash)
{
	Career7B00 *entry = FindCareer7B00WithHash0(hash);
	if (entry)
		return entry;
	entry = &field_7B00[numUsed7B00++];
	entry->hash = hash;
	return entry;
}
