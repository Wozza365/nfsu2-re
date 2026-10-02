// PROFILE: game
// GetPlayerInstanceFromC, 8 bytes
// yugecin's prototype: struct C4 *__cdecl GetPlayerInstanceFromC(struct C *c);
struct C4;
struct C { int f0; C4 *playerInstance; };

// FUNCTION: 0x004A9D50
C4 *GetPlayerInstanceFromC(C *c)
{
	return c->playerInstance;
}
