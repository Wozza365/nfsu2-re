// PROFILE: game
// DeletePool, 16 bytes
// yugecin's prototype: int __cdecl DeletePool(struct Pool *pool);
struct Pool;
struct PoolControl {
	int DeletePool(Pool *pool);
};
extern PoolControl pools;

// FUNCTION: 0x00440E40
int DeletePool(Pool *pool)
{
	return pools.DeletePool(pool);
}
