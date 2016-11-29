#ifndef _HALFLING_H_
#define _HALFLING_H_

#include "Character.h"
class Generator;


class Halfling final: public Character {
private:
		// override to add 50% chance to miss
		virtual bool takeDamageFrom(Character& attacker, 
			int& damage, Generator& rng) override;

public:
	Halfling(int wallet);

};


#endif


