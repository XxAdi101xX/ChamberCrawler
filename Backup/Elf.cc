#include <Elf.h>
using namespace std;

class Character;
class Generator;


void Elf::attack(Character& defender, Generator& rng) {}


void Elf::setStats() {
        this->HPMax = 140;
        this->HP = 140;
        this->attack = 30;
        this->defence = 10;
}


