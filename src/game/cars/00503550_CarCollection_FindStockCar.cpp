// PROFILE: game
// CarCollection::FindStockCar, 50 bytes
// yugecin's prototype: struct StockCar *__thiscall CarCollection__FindStockCar(struct CarCollection *this, unsigned int stockCarHash);
// yugecin's note: stockCarHash like STOCK_PEUGOT
#include "game/CarCollection.h"

// Defined inline in CarCollection.h (IsStockCar inlines it); this emits the out-of-line copy.
// FUNCTION: 0x00503550 SYMBOL=?FindStockCar@CarCollection@@QAEPAUStockCar@@I@Z
typedef StockCar *(CarCollection::*FindStockCarFn)(unsigned int);
FindStockCarFn emit_FindStockCar() { return &CarCollection::FindStockCar; }
