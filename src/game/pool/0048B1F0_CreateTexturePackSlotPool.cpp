// PROFILE: game
// CreateTexturePackSlotPool, 28 bytes
// yugecin's prototype: void __cdecl CreateTexturePackSlotPool();
struct Pool;
Pool *CreatePool(int elementSize, int elementAmount, char *name, int unknown);
extern Pool *texturePackSlotPool;

// FUNCTION: 0x0048B1F0
void CreateTexturePackSlotPool()
{
	texturePackSlotPool = CreatePool(0x7C, 0x80, "TexturePackSlotPool", 0);
}
