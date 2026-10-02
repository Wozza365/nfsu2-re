// PROFILE: game
// func, 26 bytes
// yugecin's prototype: int __cdecl func(int, int);
struct Obj43CAE0 { char pad[0xa]; unsigned short offset; };

// FUNCTION: 0x0043CAE0
int func(Obj43CAE0 *a, Obj43CAE0 *b)
{
	char *pa = (char *)a - a->offset;
	char *pb = (char *)b - b->offset;
	return pb >= pa;
}
