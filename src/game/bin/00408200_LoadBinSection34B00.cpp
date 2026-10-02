// PROFILE: game
// LoadBinSection34B00, 29 bytes
// yugecin's prototype: int __cdecl LoadBinSection34B00(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
extern char *g_81CB60;

// FUNCTION: 0x00408200
int LoadBinSection34B00(BinSection *bindata)
{
	if (bindata->magic == 0x34B00) {
		g_81CB60 = bindata->data;
		return 1;
	}
	return 0;
}
