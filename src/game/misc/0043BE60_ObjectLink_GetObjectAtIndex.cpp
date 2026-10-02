// PROFILE: game
// ObjectLink::GetObjectAtIndex, 31 bytes
// yugecin's prototype: struct ObjectLink *__thiscall ObjectLink__GetObjectAtIndex(struct ObjectLink *this, int index);
#include "game/ObjectLink.h"

// FUNCTION: 0x0043BE60
ObjectLink *ObjectLink::GetObjectAtIndex(int index)
{
	int i = 0;
	ObjectLink *p;
	for (p = next; p != this; p = p->next) {
		if (i == index)
			break;
		i++;
	}
	return p;
}
