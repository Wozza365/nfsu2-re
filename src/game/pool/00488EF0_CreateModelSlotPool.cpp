// PROFILE: game
// CreateModelSlotPool, 28 bytes
// yugecin's prototype: void __cdecl CreateModelSlotPool();
struct Pool;
Pool *CreatePool(int elementSize, int elementAmount, char *name, int unknown);
extern Pool *eModelSlotPool;

// FUNCTION: 0x00488EF0
void CreateModelSlotPool()
{
	eModelSlotPool = CreatePool(0x18, 5000, "eModelSlotPool", 0);
}
