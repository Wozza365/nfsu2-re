// PROFILE: game
// Career4230::GetMenuCarInstanceAtIndex, 17 bytes
// yugecin's prototype: struct MenuCarInstance *__thiscall Career4230__GetMenuCarInstanceAtIndex(struct Career4230 *this, int index);
// yugecin's note: index 0-2
#include "game/Career4230.h"

// FUNCTION: 0x00500D00
MenuCarInstance *Career4230::GetMenuCarInstanceAtIndex(int index)
{
	return &field_10[index];
}
