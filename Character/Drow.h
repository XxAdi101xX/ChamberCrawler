#ifndef _DROW_H_
#define _DROW_H_

#include "Character.h"
class Potion;


class Drow final: public Character {
private:
	// overrides the normal addHPViaPotion
	// to amplify effects by 50% 
	virtual void addHPViaPotion(int amount) override;
	virtual int getTotalAttack() override; // amplfies potion effects by 50%
	virtual int getTotalDefence() override; // amplifies potion effects by 50%

public:
	Drow(int wallet); // ctor

};


#endif


