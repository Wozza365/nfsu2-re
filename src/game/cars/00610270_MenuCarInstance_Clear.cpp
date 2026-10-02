// PROFILE: game
// MenuCarInstance::Clear, 115 bytes
// yugecin's prototype: void __thiscall MenuCarInstance__Clear(struct MenuCarInstance *this, int carIndex, int unused, char field5, char field6);
#include <string.h>
#include "game/MenuCarInstance.h"

// FUNCTION: 0x00610270
void MenuCarInstance::Clear(int carIndex, int unused, char field5, char field6)
{
	this->carIndex = carIndex;
	field_5 = field5;
	field_6 = field6;
	field_4 = 0;
	field_7 = 1;
	field_580 = 0xFF;
	field_581 = 0;
	someDummySkinHash = 0;
	field_8E8 = 0;
	memset(field_590, 0, sizeof(field_590));
	memset(field_838, 1, sizeof(field_838));
	field_8E4 = 0;
	field_10.Clear(this->carIndex);
}
