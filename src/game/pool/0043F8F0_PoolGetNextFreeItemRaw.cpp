// PROFILE: game
// PoolGetNextFreeItemRaw, 34 bytes
// yugecin's prototype: struct PoolEntry *__cdecl PoolGetNextFreeItemRaw(struct Pool *pool);
struct PoolEntry { PoolEntry *nextEntry; PoolEntry *prevEntry; };
struct Pool {
	void *prev; void *next; Pool *nextLinkedPool; char *pName;
	PoolEntry *firstAvailableElement; int flags; int numUsedElements; int maxUsedElements_;
	unsigned int unknownArgGivenOnPoolCreation; int elementAmount; int elementSize;
	int elementAmountOverAllLinkedPools;
	PoolEntry *GetNextFreeItem();
};

// FUNCTION: 0x0043F8F0
PoolEntry *PoolGetNextFreeItemRaw(Pool *pool)
{
	int n = pool->numUsedElements + 1;
	PoolEntry *e = pool->firstAvailableElement;
	if (e) {
		PoolEntry *next = e->nextEntry;
		if (n > pool->maxUsedElements_)
			pool->maxUsedElements_ = n;
		pool->firstAvailableElement = next;
		pool->numUsedElements = n;
	}
	return e;
}
