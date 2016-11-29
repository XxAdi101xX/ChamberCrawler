#ifndef _ORC_H_
#define _ORC_H_

#include "Character.h"
class Generator;


class Orc final: public Character {
private:
		// overrides to deal double damage to Goblin
		virtual bool dealDamageTo(Character& defender, 
			int& damage, Generator& rng) override;

public:
	Orc(int wallet); // ctor

};


#endif


