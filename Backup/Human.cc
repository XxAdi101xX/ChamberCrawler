#include "Human.h"
using namespace std;

class Character;


void Human::deathRoutine() {}


void Human::setStats() {
	this->HPMax = 140;
        this->HP = 140;
        this->attack = 20;
        this->defence = 20;
}


