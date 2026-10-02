// PROFILE: game
struct Allocator { virtual void v0(); virtual void Free(void *p, int a); };
void GetAllocator(Allocator **out);
void sub_734E40();
void sub_734E60();
struct Thing { void sub_735550(); };
struct Inner { Thing *f0; };
struct Base47 { virtual ~Base47() {} };
struct Derived47 : Base47 { char pad[0x190]; Inner *f194; virtual ~Derived47(); };
// FUNCTION: 0x0047D470
Derived47::~Derived47()
{
	Inner *p = f194;
	if (p) {
		if (p->f0)
			p->f0->sub_735550();
		Allocator *a;
		GetAllocator(&a);
		sub_734E40();
		a->Free(p, 0);
		sub_734E60();
		f194 = 0;
	}
}
