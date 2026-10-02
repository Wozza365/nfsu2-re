// PROFILE: game
// Jumbo file: compiled as one unit, like EA's z*.cpp source lists (the Most Wanted decomp has
// zFe.cpp, zMisc.cpp, ... that #include many .cpp files). The name is ours; EA's list for this part
// of the game isn't known. The files are included in the order of their functions in the exe.
//
// Why these belong together: FindCareer7B00WithHash0 (5003B0) is inlined into 500460, 500B80,
// 501150 and 512F10, and 512FF0 calls it and 512F10 assuming ecx survives, which the compiler only
// does for functions it has already compiled in the same unit. 5410E0 relies on the same for 512F10.
// GetRaceCategory (5002E0) is static and takes its argument in eax, which only works for callers in
// the same unit (5007A0). The same goes for sub_514340 (race in edx, id in edi) and 5143C0.
// 5130A0 keeps the race count in a register across calls to 500B80: the compiler knew 500B80
// doesn't change it.
#include "career/005002E0_GetRaceCategory.cpp"
#include "career/005003B0_Career_FindCareer7B00WithHash0.cpp"
#include "career/00500460_Career_500460.cpp"
#include "career/005007A0_Career7148_5007A0.cpp"
#include "career/00500B80_Career_500B80.cpp"
#include "career/00501150_Career4210_501150.cpp"
#include "career/00512F10_Career_512F10.cpp"
#include "career/00512FF0_Career_512FF0.cpp"
#include "career/005130A0_Career_5130A0.cpp"
#include "career/00513110_Career_ShouldShowShopOnMap.cpp"
#include "career/00513490_CareerStage_513490.cpp"
#include "career/005138F0_Career_5138F0.cpp"
#include "career/00514340_RaceHasFlagOrIsDone.cpp"
#include "career/005143C0_Career_5143C0.cpp"
#include "career/00528500_Career_528500.cpp"
#include "career/005410E0_Career_5410E0.cpp"
