// PROFILE: game
// ProfileData::GetCarCollection, 34 bytes
// yugecin's prototype: struct CarCollectionWithPointers *__thiscall ProfileData__GetCarCollection(struct ProfileData *this, int playerIndex);
struct CarCollectionWithPointers { char data[0xAB4C]; };
struct ProfileData {
	char pad[0x3C0];
	CarCollectionWithPointers carCollections[2];
	CarCollectionWithPointers *GetCarCollection(int playerIndex);
};

// FUNCTION: 0x00495240
CarCollectionWithPointers *ProfileData::GetCarCollection(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 2)
		return &carCollections[playerIndex];
	return 0;
}
