#include "Halfling.h"
//#include "Generator.h"
using namespace std;


Halfling::Halfling(int wallet): Character{100, 100, 15, 20, true, Race::Halfling, wallet} {}


bool Halfling::takeDamageFrom(Character& attacker, 
	int& Damage, Generator& rng) {
	return rng.genHitMiss();
}


