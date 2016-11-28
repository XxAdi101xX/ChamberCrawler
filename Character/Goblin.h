#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "Character.h"


class Goblin final: public Character {
private:
	// overrides to add 5 gold if target is killed
	virtual void postAttackRoutine(Character& defender, 
	bool hit, Generator& rng) override;

public:
	Goblin(int wallet); // ctor

};


#endif


