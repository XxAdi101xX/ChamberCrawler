#include "Elf.h"
#include "../Enumerations/Race.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;
class Generator;


Elf::Elf(int wallet): Character{ELF_HP_MAX, ELF_HP,
	ELF_ATTACK_VALUE, ELF_DEFENCE_VALUE, true, Race::Elf, wallet},
	extraAttacks{ELF_NUMBER_OF_EXTRA_ATTACKS} {}

void Elf::postAttackRoutine(Character& defender, bool hit, Generator& rng) {
	// not attacking again if already attacked or target is Drow
	if (extraAttacks == 0 || defender.getRace() == Race::Drow) {
		this->extraAttacks = ELF_NUMBER_OF_EXTRA_ATTACKS;
		return;
	}

	--(this->extraAttacks);

	// recursive call to attack, attack will
	// call postAttackRoutine again, but
	// will get stopped by base case
	this->attack(defender, rng);

}
