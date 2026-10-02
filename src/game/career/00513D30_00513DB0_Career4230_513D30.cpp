// PROFILE: game
// Career4230::513D30, 128 bytes, and Career4230::513DB0, 76 bytes
// yugecin's prototypes: int __thiscall Career4230__513D30(struct Career4230 *this);
//                       void __thiscall Career4230__513DB0(struct Career4230 *this);
// One file: 513DB0 keeps using ecx after calling 513D30, which the compiler only does when it
// can see that 513D30 leaves ecx alone.
#include "game/Career4230.h"
#include "game/Career.h"
#include "game/CareerStageSettings.h"

extern int g_8654A4;
extern int g_89E7B0;
extern float g_865154;

// FUNCTION: 0x00513D30
bool Career4230::sub_513D30()
{
	int stage = g_85AD40.currentStage;
	if (stage > 5)
		return true;
	int limit = g_85AD40.stages[stage].settings->field_40;
	int raced = g_85AD40.stages[stage].outrunsRaced;
	bool ok;
	if (stage == 0 && g_85AD40.field_873D)
		ok = false;
	else
		ok = true;
	if (stage == 0 && g_85AD40.field_873E)
		ok = false;
	if (!g_85AD40.field_C00.field_8 && ok && (raced < limit || limit == -1) && floatField_1AE4 < 0.0f)
		return true;
	return false;
}

// FUNCTION: 0x00513DB0
void Career4230::sub_513DB0()
{
	if (g_8654A4 == 6 && !g_89E7B0) {
		floatField_1AE4 -= g_865154;
		if (!field_1AE8 && sub_513D30()) {
			field_1AE8 = 1;
			field_1AE0 = 7;
		}
	}
}
