// PROFILE: lib_o1
int fn_72A672();
struct S72 { int (*fn)(); int f4, f8, fc, f10, f14; char pad18[3]; char f1b; float f1c; };
// FUNCTION: 0x0072A6BE
int init72A6BE(S72 *p)
{
	p->f1c = 0.0f;
	p->f8 = 0; p->fc = 0; p->f10 = 0; p->f14 = 0;
	p->f1b = 0;
	p->f4 = 0;
	p->fn = fn_72A672;
	return 0;
}
