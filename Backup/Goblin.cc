#include "Goblin.h"
#include "Race.h"
#include "Defines.cc"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;


Goblin::Goblin(int wallet): Character{GOBLIN_HP_MAX, GOBLIN_HP, 
	GOBLIN_ATTACK_VALUE, GOBLIN_DEFENCE_VALUE, 
	true, Race::Goblin, wallet} {}


void Goblin::postAttackRoutine(Character& defender, bool hit, Generator& rng) {
	// if defender is dead, and goblin killed it
	if (defender.getHP() <= 0 && hit) {
		this->addGold(GOBLIN_LOOT_BONUS);
	}

}


