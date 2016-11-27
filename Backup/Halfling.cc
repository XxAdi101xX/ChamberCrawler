#include <Halfling.h>
using namespace std;

class Generator;


bool Halfling::defend(int incomingDamage, Generator& rng) {}


void Halfling::setStats() {
        this->HPMax = 100;
        this->HP = 100;
        this->attack = 15;
        this->defence = 20;
}


