// PROFILE: game
// UnloadBinSection8003B200_8003B201_8003B202, 40 bytes
// yugecin's prototype: int __cdecl UnloadBinSection8003B200_8003B201_8003B202(struct BinSection *bindata);
struct BinSection { unsigned int magic; int size; char data[1]; };
struct Obj828770 {
	void sub_452D50(BinSection *bindata);
};
extern Obj828770 g_828770;

// FUNCTION: 0x00452E90
int UnloadBinSection8003B200_8003B201_8003B202(BinSection *bindata)
{
	if (bindata->magic >= 0x8003B200 && bindata->magic <= 0x8003B202) {
		g_828770.sub_452D50(bindata);
		return 1;
	}
	return 0;
}
