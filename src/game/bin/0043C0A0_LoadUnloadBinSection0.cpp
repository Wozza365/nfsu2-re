// PROFILE: game
// LoadUnloadBinSection0, 14 bytes
// yugecin's prototype: int __cdecl LoadUnloadBinSection0(struct BinSection *binsection);
// yugecin's note: Nop handler that returns {1} if {binsection->{struct BinSection+0}} is {0}.
struct BinSection { unsigned int magic; int size; char data[1]; };

// FUNCTION: 0x0043C0A0
int LoadUnloadBinSection0(BinSection *binsection)
{
	return binsection->magic == 0;
}
