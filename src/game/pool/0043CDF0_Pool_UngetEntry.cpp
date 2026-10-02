// PROFILE: game
// Pool::UngetEntry, 24 bytes
// yugecin's prototype: int __thiscall Pool__UngetEntry(struct Pool *this, struct PoolEntry *entry);
// yugecin's note: Mark the entry as free again. Returns the amount of used entries in the pool.
struct PoolEntry { PoolEntry *nextEntry; PoolEntry *prevEntry; };
struct Pool {
	void *prev; void *next; Pool *nextLinkedPool; char *pName;
	PoolEntry *firstAvailableElement; int flags; int numUsedElements; int maxUsedElements_;
	unsigned int unknownArgGivenOnPoolCreation; int elementAmount; int elementSize;
	int elementAmountOverAllLinkedPools;
	int UngetEntry(PoolEntry *entry);
};

// FUNCTION: 0x0043CDF0
int Pool::UngetEntry(PoolEntry *entry)
{
	int n = numUsedElements;
	entry->nextEntry = firstAvailableElement;
	numUsedElements = --n;
	firstAvailableElement = entry;
	return n;
}
