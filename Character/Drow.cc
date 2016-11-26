#include "Drow.h"
using namespace std;

class Potion;


void Drow::applyPotion(Potion& potion) {}


int Drow::getAttack() {}


int Drow::getDefence() {}


void Drow::setStats() {
	this->HPMax = 150;
        this->HP = 150;
        this->attack = 25;
        this->defence = 15;
}


