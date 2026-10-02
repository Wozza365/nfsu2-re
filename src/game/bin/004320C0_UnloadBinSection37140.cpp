// PROFILE: game
// UnloadBinSection37140, 37 bytes
// yugecin's prototype: int __cdecl UnloadBinSection37140(struct BinSection *bindata);
#include "bWare/bList.h"
struct BinSection { unsigned int magic; int size; char data[1]; };

// FUNCTION: 0x004320C0
int UnloadBinSection37140(BinSection *bindata)
{
	if (bindata->magic == 0x37140) {
		bNode *node = (bNode *)(((int)bindata->data + 15) & ~15);
		node->Remove();
		return 1;
	}
	return 0;
}
