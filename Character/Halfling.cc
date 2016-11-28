#include "Halfling.h"
//#include "Generator.h"
#include "Defines.cc"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc


Halfling::Halfling(int wallet): Character{HALFLING_HP_MAX, HALFLING_HP, 
	HALFLING_ATTACK_VALUE, HALFLING_DEFENCE_VALUE, 
	true, Race::Halfling, wallet} {}


bool Halfling::takeDamageFrom(Character& attacker, 
	int& damage, Generator& rng) {
	return rng.genHitMiss();
}


