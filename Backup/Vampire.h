#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "Character.h"


class Vampire final: public Character {
private:
	// override adds health if enemy was hit
	virtual void postAttackRoutine(Character& defender, 
		bool hit, Generator& rng) override;

public:	
	Vampire(int wallet);

};


#endif


