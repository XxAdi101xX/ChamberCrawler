#include "Drow.h"
#include "../Enumerations/Race.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Potion;


Drow::Drow(int wallet): Character{DROW_HP_MAX, DROW_HP,
	DROW_ATTACK_VALUE, DROW_DEFENCE_VALUE, true, Race::Drow, wallet} {}


void Drow::addHPViaPotion(int amount) {
	this->addHP(amount * (1 + DROW_POTION_BONUS));
}


int Drow::getAttackBuffBonus() const {
	return DROW_POTION_BONUS * this->getAttackBuffProt();
}


int Drow::getDefenceBuffBonus() const {
		return DROW_POTION_BONUS * this->getDefenceBuffProt();
}
