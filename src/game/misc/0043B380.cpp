// PROFILE: game
// NONMATCHING (one byte short): the switch on f28 is lowered as sub/dec/dec in the original, a
// test for case 0 then 1 then 2; every shape tried here gives a range check or drops the case-0 test.
// Tried: cases 1/2 merged or separate, explicit case 0 and default, switching on an enum, the switch
// inside an inline helper. The list iteration (EA's bTList) matches. Identical on compilers 3052/3077.
#include "bWare/bList.h"
extern bool g_827C38;
struct SoundSys { void sub_4791B0(int a); };
extern SoundSys *g_82B884;
void sub_61F5A0(int a);
void sub_439930();
struct ItemBase { virtual ~ItemBase(); char pad[0xc]; };
struct Item : ItemBase, bTNode<Item> {
	int f18; char pad1c[0xc]; int f28; int f2c; char pad30[0xf0]; int f120;
	void sub_439070(); void sub_437A80(); void sub_4391B0();
};
struct Mgr {
	int f0; bTList<Item> list;
	Item *sub_432490(int id);
	bool f(bool arg);
};
// FUNCTION: 0x0043B380
bool Mgr::f(bool arg)
{
	bool any = false;
	Item *next;
	for (Item *it = list.GetHead(); it != list.EndOfList(); it = next) {
		next = it->GetNext();
		if (g_827C38)
			g_82B884->sub_4791B0(0);
		switch (it->f28) {
		case 0: break;
		case 1: case 2:
			it->f28 = 0;
			it->sub_439070();
			it->f2c = 0;
			break;
		}
		if (arg) {
			Item *o = sub_432490(it->f18);
			if (o) {
				o->sub_437A80();
				o->sub_4391B0();
				sub_61F5A0(o->f120);
				sub_439930();
				o->Remove();
				delete o;
			}
		}
		if (!any)
			any = true;
	}
	return any;
}
