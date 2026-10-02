// PROFILE: game
// strncpy, 40 bytes (EA's bStrNCpy; renamed to avoid the CRT intrinsic)
// yugecin's prototype: void __cdecl strncpy(char *dst, char *src, int maxlen);

// FUNCTION: 0x0043DC00
char *bStrNCpy(char *dst, const char *src, int maxlen)
{
	int i = 0;
	while (maxlen != 0) {
		char c = src[i];
		maxlen--;
		dst[i] = c;
		if (c == 0)
			break;
		i++;
	}
	return dst;
}
