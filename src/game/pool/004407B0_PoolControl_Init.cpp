// PROFILE: game
// PoolControl::Init, 17 bytes (the constructor of the global PoolControl at 0x828530)
// yugecin's prototype: void __thiscall PoolControl__Init(struct PoolControl *this);
struct PoolLink {
	PoolLink *prev;
	PoolLink *next;
	PoolLink() { prev = this; next = this; }
};
struct PoolControl {
	int inited;
	PoolLink link;
	PoolControl();
};

// FUNCTION: 0x004407B0
PoolControl::PoolControl()
{
	inited = 1;
}
