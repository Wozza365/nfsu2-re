// PROFILE: game
struct Pool {
	char pad[0xc]; unsigned short elemSize; unsigned short count; unsigned char bits[4]; char *base;
	void *Alloc();
};
// FUNCTION: 0x00504400
void *Pool::Alloc()
{
	if (count == 32)
		return 0;
	unsigned int i = 0;
	while (bits[i] == 0xff)
		i++;
	i <<= 3;
	while (bits[i >> 3] & (1 << (i & 7)))
		i++;
	count++;
	bits[i >> 3] |= (unsigned char)(1 << (i & 7));
	return base + elemSize * i;
}
