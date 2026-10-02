// PROFILE: game
// StockCar::ApplyTuningToInstance, 82 bytes
// yugecin's prototype: void *__thiscall StockCar__ApplyTuningToInstance(struct StockCar *this, int playerIndex, struct MenuCarInstance *menuCarInstance, int);
#include "game/StockCar.h"
#include "game/MenuCarInstance.h"

// FUNCTION: 0x00503A80
void StockCar::ApplyTuningToInstance(int playerIndex, MenuCarInstance *menuCarInstance, int a3)
{
	menuCarInstance->Clear(indexInCarData, 1, 0, 0);
	menuCarInstance->CalculateSomeHashes(playerIndex + 1);
	menuCarInstance->sub_637040(playerIndex);
	floatField_C = menuCarInstance->field_10.sub_5B6990(0, -1.0f);
	menuCarInstance->GetField590AtIndex(0x3F);
}
