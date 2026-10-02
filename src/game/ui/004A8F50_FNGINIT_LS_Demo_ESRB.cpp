// PROFILE: game
void *operator new(unsigned int size);
struct FNGObject { FNGObject(void *a); virtual ~FNGObject(); char pad[0x48]; };
extern int g_8651AC;
struct DemoESRBFNGObject : FNGObject {
	struct Z { int v; Z() : v(0) {} } f4c;
	DemoESRBFNGObject(void *a) : FNGObject(a) { f4c.v = g_8651AC; }
};
// FUNCTION: 0x004A8F50
FNGObject *FNGINIT_LS_Demo_ESRB(void *a) { return new DemoESRBFNGObject(a); }
