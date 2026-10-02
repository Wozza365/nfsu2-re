// PROFILE: game
// cshash, 33 bytes (EA's bStringHash)
// yugecin's prototype: unsigned int __cdecl cshash(char *str);
// yugecin's note: Case sensitive hash function. see also {43DB80} and {505450}

// FUNCTION: 0x0043DB50
unsigned int cshash(const char *str)
{
	unsigned int h = -1;
	while (*str) {
		h = h * 33 + (unsigned char)*str;
		str++;
	}
	return h;
}
