// PROFILE: game
// GetDByIndex, 16 bytes
// yugecin's prototype: struct D *__cdecl GetDByIndex(int index);
// yugecin's note: returns {832DE0} at requested index
struct D { char data[0x70]; };
extern D d[];

#pragma optimize("y", off)
// FUNCTION: 0x0048B1E0
D *GetDByIndex(int index)
{
	return &d[index];
}
#pragma optimize("", on)
