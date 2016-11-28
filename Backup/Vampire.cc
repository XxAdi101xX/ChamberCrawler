#include "Vampire.h"
#include "Defines.cc"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;


Vampire::Vampire(int wallet): Character{VAMPIRE_HP_MAX, VAMPIRE_HP,
        VAMPIRE_ATTACK_VALUE, VAMPIRE_DEFENCE_VALUE, true, Race::Vampire, wallet} {}


void Vampire::postAttackRoutine(Character& defender, bool hit, Generator& rng) {
	// calculates potential HP gain/loss
	int HPToBeAdded = defender.getRace() == Race::Dwarf 
		? -1 * VAMPIRE_ON_HIT_HEAL : VAMPIRE_ON_HIT_HEAL;

	// only add if actually hit enemy
	if (hit) {
		this->addHP(HPToBeAdded);
	}

}


