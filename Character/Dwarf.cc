#include "Dwarf.h"
#include "../Enumerations/Race.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

Dwarf::Dwarf(int wallet): Character{DWARF_HP_MAX, DWARF_HP,
	DWARF_ATTACK_VALUE, DWARF_DEFENCE_VALUE, true, Race::Dwarf, wallet} {}
