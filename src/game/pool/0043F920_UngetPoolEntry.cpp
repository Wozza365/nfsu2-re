// PROFILE: game
// UngetPoolEntry, 26 bytes
// yugecin's prototype: int __cdecl UngetPoolEntry(struct Pool *pool, struct PoolEntry *entry);
// yugecin's note: Same as {43CDF0}, but a cdecl.
// Unlike 43CDF0 this one returns nothing: eax is left holding the pool.
struct PoolEntry { PoolEntry *nextEntry; PoolEntry *prevEntry; };
struct Pool {
	void *prev; void *next; Pool *nextLinkedPool; char *pName;
	PoolEntry *firstAvailableElement; int flags; int numUsedElements; int maxUsedElements_;
	unsigned int unknownArgGivenOnPoolCreation; int elementAmount; int elementSize;
	int elementAmountOverAllLinkedPools;
	PoolEntry *GetNextFreeItem();
};

// FUNCTION: 0x0043F920
void UngetPoolEntry(Pool *pool, PoolEntry *entry)
{
	int n = pool->numUsedElements;
	entry->nextEntry = pool->firstAvailableElement;
	pool->numUsedElements = --n;
	pool->firstAvailableElement = entry;
}
