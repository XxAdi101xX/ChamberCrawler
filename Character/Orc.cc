#include "Orc.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Generator;


Orc::Orc(int wallet): Character{ORC_HP_MAX, ORC_HP,
	ORC_ATTACK_VALUE, ORC_DEFENCE_VALUE, true, Race::Orc, wallet} {}

bool Orc::dealDamageTo(Character& defender, int& damage, Generator& rng) {
	// if race is goblin, deal 50% more damage
	if (defender.getRace() == Race::Goblin) {
		damage *= 1.5;
	}

	return true;
}
