#include "Merchant.h"
using namespace std;

class Character;


void Merchant::deathRoutine(Character& killer) {}


void Merchant::setStats() {
        this->HPMax = 30;
        this->HP = 30;
        this->attack = 70;
        this->defence = 5;
	this->isHostile = false;
}


