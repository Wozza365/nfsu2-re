// PROFILE: game
// CareerStage::IncreaseRacesFinishedAndAddReputation, 94 bytes
// yugecin's prototype: void __thiscall CareerStage__IncreaseRacesFinishedAndAddReputation(struct CareerStage *this, int, struct CareerRace *race);
// yugecin's note: does nothing if the race is DDAY_EVENT_A or DDAY_EVENT_B
#include "game/CareerStage.h"
#include "game/CareerRace.h"

float CalculateReputationToAddFromWonRace(float a1, CareerRace *race);

static inline bool HashIs(unsigned int hash, char *name) { return hash == cshash(name); }

// FUNCTION: 0x00513430
void CareerStage::IncreaseRacesFinishedAndAddReputation(float a1, CareerRace *race)
{
	if (!HashIs(race->hash, "DDAY_EVENT_A") && !HashIs(race->hash, "DDAY_EVENT_B")) {
		totalReputation += CalculateReputationToAddFromWonRace(a1, race);
		racesFinished++;
	}
}
