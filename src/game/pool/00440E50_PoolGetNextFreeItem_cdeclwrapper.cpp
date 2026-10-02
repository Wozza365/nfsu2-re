// PROFILE: game
// PoolGetNextFreeItem_cdeclwrapper, 9 bytes
// yugecin's prototype: struct PoolEntry *__cdecl PoolGetNextFreeItem_cdeclwrapper(struct Pool *pool);
struct PoolEntry { PoolEntry *nextEntry; PoolEntry *prevEntry; };
struct Pool {
	void *prev; void *next; Pool *nextLinkedPool; char *pName;
	PoolEntry *firstAvailableElement; int flags; int numUsedElements; int maxUsedElements_;
	unsigned int unknownArgGivenOnPoolCreation; int elementAmount; int elementSize;
	int elementAmountOverAllLinkedPools;
	PoolEntry *GetNextFreeItem();
};

// FUNCTION: 0x00440E50
PoolEntry *PoolGetNextFreeItem_cdeclwrapper(Pool *pool)
{
	return pool->GetNextFreeItem();
}
