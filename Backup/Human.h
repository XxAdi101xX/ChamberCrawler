#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Character.h"


class Human final: public Character {
public:
	// overrides to drop two normal goldpile upon death
        virtual void deathRoutine() override;
	virtual void setStats() override; // sets Human stats

};


#endif


