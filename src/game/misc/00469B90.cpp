// PROFILE: game
struct Obj469 {
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	char pad[0x4c]; Obj469 *next;
};
struct S469B90 {
	char pad0[0x20]; Obj469 *head; char pad24[0x0c]; int f30; char pad34[0x08];
	bool f3c; char pad3d[3]; int f40;
	bool f();
};
// FUNCTION: 0x00469B90
bool S469B90::f()
{
	f40 = 0;
	f3c = false;
	for (Obj469 *p = head; p; p = p->next)
		p->v12();
	f30 = 0;
	return true;
}
