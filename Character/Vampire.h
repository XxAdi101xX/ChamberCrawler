#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include <Character.h>


class Vampire final: public Character {
private:
	// override adds health after attack
	virtual void postAttackRoutine(Character& defender) override;

public:	
	virtual void setStats() override; // sets Vampire stats

};


#endif


