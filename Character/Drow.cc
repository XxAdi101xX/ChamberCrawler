#include "Drow.h"
#include "Race.h"
using namespace std;

class Potion;


Drow::Drow(int wallet): Character{150, 150, 25, 15, true, Race::Drow, wallet} {}


void Drow::addHPViaPotion(int amount) {
	this->addHP(amount * 1.5);
}


int Drow::getAttackBuffBonus() {
	return 0.5 * this->getAttackBuffProt();
}


int Drow::getDefenceBuffBonus() {
        return 0.5 * this->getDefenceBuffProt();
}


