#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Character.h"


class Human final: public Character {
public:
	Human(int wallet); // ctor

	// overrides to drop two normal GoldPile upon death
        virtual void deathRoutine() override;

};


#endif


