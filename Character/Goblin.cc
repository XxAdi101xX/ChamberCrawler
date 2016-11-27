#include "Goblin.h"
#include "Race.h"
using namespace std;

class Character


Goblin::Goblin(int wallet): Character{110, 110, 15, 20, true, Race::Goblin, wallet} {}


void Goblin::postAttackRoutine(Character& defender, Generator& rng) {
	int goblinBonusGoldAmount = 5;

	if (defender.getHP() <= 0) {
		this->addGold(goblinBonusGoldAmount)
	}

}


