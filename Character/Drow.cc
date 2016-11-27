#include "Drow.h"
using namespace std;

class Potion;


void Drow::addHPViaPotion(int amount) {
	this->addHP(amount * 1.5);
}


int Drow::getTotalAttack() {
	return this->getAttackValue() + 1.5 * this->getAttackBuff();
}


int Drow::getTotalDefence() {
        return this->getDefenceValue() + 1.5 * this->getDefenceBuff();
}


void Drow::setStats() {
	this->setHPMax(150);
        this->setHP(150);
        this->setAttackValue(25);
        this->setDefenceValue(15);
}


