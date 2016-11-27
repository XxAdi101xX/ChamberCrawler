#include <Dragon.h>
using namespace std;

class Character;


void Dragon::deathRoutine(Character& killer) {}


void Dragon::endTurnRoutine() {}


void Dragon::setStats() {
	this->HPMax = 150;
	this->HP = 150;
	this->attack = 20;
	this->defence = 20;
	this->isHostile = false;
}


