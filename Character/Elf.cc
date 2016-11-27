#include "Elf.h"
#include "Race.h"
using namespace std;

class Character;
class Generator;


Elf::Elf(int wallet): Character{140, 140, 30, 10, true, Race::Elf, wallet}, 
	attackedTwice{false} {}


void Elf::postAttackRoutine(Character& defender, Generator& rng) {
	if (this->attackedTwice) {
		this->attackedTwice = false;
		return;
	}

	this->attackedTwice = true;
	
	// recursive call to attack, attack will
	// call postAttackRoutine again, but
	// will get stopped by base case
	this->attack(defender, rng);

}


