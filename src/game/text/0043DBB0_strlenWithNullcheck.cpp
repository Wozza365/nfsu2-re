// PROFILE: game
// strlenWithNullcheck, 26 bytes (EA's bStrLen)
// yugecin's prototype: int __cdecl strlenWithNullcheck(char *str);

// FUNCTION: 0x0043DBB0
int strlenWithNullcheck(const char *str)
{
	int len = 0;
	if (str) {
		while (str[len])
			len++;
	}
	return len;
}
