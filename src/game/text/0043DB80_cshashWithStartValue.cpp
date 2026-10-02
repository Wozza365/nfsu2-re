// PROFILE: game
// cshashWithStartValue, 33 bytes (EA's bStringHash with a prefix hash)
// yugecin's prototype: unsigned int __cdecl cshashWithStartValue(char *str, unsigned int startValue);
// yugecin's note: Like {43DB50}, but starts with given {startValue} instead of {-1}.

// FUNCTION: 0x0043DB80
unsigned int cshashWithStartValue(const char *str, unsigned int startValue)
{
	unsigned int h = startValue;
	while (*str) {
		h = h * 33 + (unsigned char)*str;
		str++;
	}
	return h;
}
