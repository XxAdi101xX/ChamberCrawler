#include "Orc.h"
using namespace std;

class Character;
class Generator;


void Orc::attack(Character& defender, Generator& rng) {}


void Orc::setStats() {
        this->HPMax = 180;
        this->HP = 180;
        this->attack = 30;
        this->defence = 25;
}


