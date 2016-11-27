#include "Elf.h"
#include "Race.h"
using namespace std;

class Character;
class Generator;


Elf::Elf(int wallet): Character{140, 140, 30, 10, Race::Elf, wallet}, 
	attackedTwice{false} {}


void Elf::postAttackRoutine(Character* defender) {}


