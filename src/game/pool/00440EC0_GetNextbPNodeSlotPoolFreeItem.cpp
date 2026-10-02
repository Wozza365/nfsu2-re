// PROFILE: game
// GetNextbPNodeSlotPoolFreeItem, 33 bytes
struct PoolEntry { PoolEntry *nextEntry; PoolEntry *prevEntry; };
struct Pool {
	void *prev; void *next; Pool *nextLinkedPool; char *pName;
	PoolEntry *firstAvailableElement; int flags; int numUsedElements; int maxUsedElements_;
	unsigned int unknownArgGivenOnPoolCreation; int elementAmount; int elementSize;
	int elementAmountOverAllLinkedPools;
	PoolEntry *GetNextFreeItem();
};
void CreatebPNodeSlotPool(int count);
extern Pool *pPNodeSlotPool;

// FUNCTION: 0x00440EC0
PoolEntry *GetNextbPNodeSlotPoolFreeItem()
{
	if (!pPNodeSlotPool)
		CreatebPNodeSlotPool(0x100);
	return pPNodeSlotPool->GetNextFreeItem();
}
