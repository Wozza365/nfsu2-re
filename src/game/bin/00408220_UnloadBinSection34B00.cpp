// PROFILE: game
// UnloadBinSection34B00, 31 bytes
// yugecin's prototype: int __cdecl UnloadBinSection34B00(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
extern char *g_81CB60;

// FUNCTION: 0x00408220
int UnloadBinSection34B00(BinSection *bindata)
{
	if (bindata->magic == 0x34B00) {
		g_81CB60 = 0;
		return 1;
	}
	return 0;
}
