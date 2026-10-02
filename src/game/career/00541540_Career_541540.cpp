// PROFILE: game
// Career::541540, 56 bytes
// yugecin's prototype: void __thiscall Career__541540(struct Career *this, int slotIndex, unsigned int stockCarHash);
// yugecin's note: changes {struct Career+8740} ||| ref also sets {this->{struct Career+873D} = 1} ||| code,ref
#include "game/Career.h"
#include "game/CarCollection.h"

extern CarCollection g_83AD90;
int FormatWithSinglePlaceholderAndHashCS43DB50(char *src, void *param);

// FUNCTION: 0x00541540
void Career::sub_541540(int slotIndex, unsigned int stockCarHash)
{
	field_873D = 1;
	activeCarSlotHash = FormatWithSinglePlaceholderAndHashCS43DB50("CAREER_SLOT_%d", (void *) slotIndex);
	g_83AD90.sub_5348E0(slotIndex, stockCarHash);
}
