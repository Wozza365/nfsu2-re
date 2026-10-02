// PROFILE: game
struct FNGInfo { char pad[0x1c]; int f1c, f20, f24, f28; };
FNGInfo *GetFNGInfoByName(char *name);
extern char *g_7FA1E0; extern bool g_838528; extern bool g_7FA1FC;
struct Inner { char pad[0xac]; bool fac; };
struct FNGArg { int f0; Inner *f4; };
struct IconScrollerFNGObject { IconScrollerFNGObject(FNGArg *a); virtual ~IconScrollerFNGObject(); char pad[0x14c]; };
struct DecalMainFNGObject : IconScrollerFNGObject {
	int f150, f154; int arr158[3]; bool arr164[3]; int f168; const char *f16c;
	bool f170, f171, f172, f173, f174;
	DecalMainFNGObject(FNGArg *a);
	void sub_5469F0();
};
// FUNCTION: 0x005530F0
DecalMainFNGObject::DecalMainFNGObject(FNGArg *a)
	: IconScrollerFNGObject(a), f150(0), f154(0), f168(2), f16c("UI_DecalsOverlayInvis.fng"),
	  f170(false), f171(false), f172(false), f173(false), f174(false)
{
	a->f4->fac = false;
	g_838528 = false;
	g_7FA1FC = true;
	for (unsigned int i = 0; i < 3; i++) {
		arr164[i] = false;
		arr158[i] = 0;
	}
	sub_5469F0();
	FNGInfo *info = GetFNGInfoByName(g_7FA1E0);
	if (info) {
		info->f1c = 0; info->f20 = 0; info->f24 = 0; info->f28 = 0;
	}
}
