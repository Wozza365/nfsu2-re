// PROFILE: game
// strcpy, 34 bytes (EA's bStrCpy; renamed to avoid the CRT intrinsic)
// yugecin's prototype: int __cdecl strcpy(char *dest, char *src);

// FUNCTION: 0x0043DBD0
char *bStrCpy(char *dest, const char *src)
{
	int i = 0;
	while ((dest[i] = src[i]) != 0)
		i++;
	return dest;
}
