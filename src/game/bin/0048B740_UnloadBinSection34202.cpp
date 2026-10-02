// PROFILE: game
// UnloadBinSection34202, 32 bytes
// yugecin's prototype: int __cdecl UnloadBinSection34202(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
extern int g_82DB14;
extern int g_82DB18;

// FUNCTION: 0x0048B740
int UnloadBinSection34202(BinSection *bindata)
{
	if (bindata->magic == 0x34202) {
		g_82DB14 = 0;
		g_82DB18 = 0;
		return 1;
	}
	return 0;
}
