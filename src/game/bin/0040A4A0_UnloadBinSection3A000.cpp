// PROFILE: game
// UnloadBinSection3A000, 37 bytes
// yugecin's prototype: int __cdecl UnloadBinSection3A000(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
extern int g_827A04;
extern int g_827A08;
extern int g_827A0C;

// FUNCTION: 0x0040A4A0
int UnloadBinSection3A000(BinSection *bindata)
{
	if (bindata->magic == 0x3A000) {
		g_827A04 = 0;
		g_827A08 = 0;
		g_827A0C = 0;
		return 1;
	}
	return 0;
}
