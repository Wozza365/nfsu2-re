// Hand-written declarations shared by game code: free functions used everywhere.
// Included at the end of the generated common.h, so every class header sees it.
#ifndef GAME_SHARED_H
#define GAME_SHARED_H

unsigned int cshash(char *str);  // 43DB50, case-insensitive string hash

// A 4-byte value that starts at zero. Arrays of these are built with the vector constructor
// iterator and the game's one shared copy of the constructor (401810, folded by the linker).
struct ZeroedU32 {
	unsigned int value;
	ZeroedU32();  // 401810, out of line in the game
};

#endif
