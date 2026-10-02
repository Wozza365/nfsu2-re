// PROFILE: game
// FreeBootflow, 27 bytes
// yugecin's prototype: void __cdecl FreeBootflow();
struct Bootflow {
	virtual ~Bootflow();
};
extern Bootflow *bootflow;

// FUNCTION: 0x004A8630
void FreeBootflow()
{
	if (bootflow)
		delete bootflow;
	bootflow = 0;
}
