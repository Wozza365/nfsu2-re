// PROFILE: game
// CarCollection::5348E0, 105 bytes
// yugecin's prototype: void __thiscall CarCollection__5348E0(struct CarCollection *this, int slotIndex, unsigned int stockCarHash);
// yugecin's note: stockCarHash like STOCK_PEUGEOT
#include "game/CarCollection.h"
#include "game/CareerCar.h"
#include "game/StockCar.h"

int FormatWithSinglePlaceholderAndHashCS43DB50(char *src, void *param);

// FUNCTION: 0x005348E0
void CarCollection::sub_5348E0(int slotIndex, unsigned int stockCarHash)
{
	CareerCar *car = GetCareerCarForSlotHash(FormatWithSinglePlaceholderAndHashCS43DB50("CAREER_SLOT_%d", (void *)slotIndex));
	StockCar *stock = FindStockCar(stockCarHash);
	car->InitializeFromStockCar(car->slotHash, stock);
	car->flags = (INVENTORY_CAR_FLAGS)4;
	car->hasCarBought = 1;
}
