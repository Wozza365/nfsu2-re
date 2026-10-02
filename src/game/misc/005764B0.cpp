// PROFILE: game
struct X5764 { char pad[0x10]; int t; };
extern X5764 *g_865134;
int perfcountertime();
// FUNCTION: 0x005764B0
void f5764B0()
{
	X5764 *p = g_865134;
	if (p)
		p->t = perfcountertime();
}
