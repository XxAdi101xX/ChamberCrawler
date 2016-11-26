#include "Vampire.h"
using namespace std;

class Character;


void Vampire::postAttackRoutine(Character& defender) {}


void Vampire::setStats() {
	this->HPMax = INT_MAX;
        this->HP = 50;
        this->attack = 25;
        this->defence = 25;
}


