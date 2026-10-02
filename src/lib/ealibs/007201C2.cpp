// PROFILE: lib_o1_frame
struct S7201 { int f0, f4, min, max, cur, target; };
void sub_7356D0(S7201 *p, int *v);

// FUNCTION: 0x007201C2
int f7201C2(S7201 *p)
{
	if (p->cur != p->target) {
		int v = p->target;
		int lo = p->min;
		int hi = p->max;
		p->cur = v;
		int a = v < lo ? lo : (v > hi ? hi : v);
		sub_7356D0(p, &a);
	}
	return 0;
}
