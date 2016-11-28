#ifndef _HALFLING_H_
#define _HALFLING_H_

#include "Character.h"
class Generator;


class Halfling final: public Character {
public:
	Halfling(int wallet);

	// override defend to add 50% chance to miss
        bool takeDamageFrom(Character& attacker, 
		int& Damage, Generator& rng) override;

};


#endif


