// PROFILE: game
// UnloadBinSection3B700, 32 bytes
// yugecin's prototype: int __cdecl UnloadBinSection3B700(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
extern int g_82DADC;
extern int g_82DAE0;

// FUNCTION: 0x0048A2B0
int UnloadBinSection3B700(BinSection *bindata)
{
	if (bindata->magic == 0x3B700) {
		g_82DADC = 0;
		g_82DAE0 = 0;
		return 1;
	}
	return 0;
}
