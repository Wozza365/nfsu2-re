// PROFILE: game
// CreateAnimCtrlPool, 28 bytes
// yugecin's prototype: void __cdecl CreateAnimCtrlPool();
struct Pool;
Pool *CreatePool(int elementSize, int elementAmount, char *name, int unknown);
extern Pool *animCtrlPool;

// FUNCTION: 0x004313B0
void CreateAnimCtrlPool()
{
	animCtrlPool = CreatePool(0x80, 0x40, "AnimCtrlSlotPool", 0);
}
