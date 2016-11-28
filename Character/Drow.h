#ifndef _DROW_H_
#define _DROW_H_

#include "Character.h"
class Potion;


class Drow final: public Character {
private:
	// overrides the normal addHPViaPotion
	// to amplify effects by 50% 
	virtual void addHPViaPotion(int amount) override;
	virtual int getAttackBuffBonus() override; // add 50% potion effects
	virtual int getDefenceBuffBonus() override; // add 50% potion effects

public:
	Drow(int wallet); // ctor

};


#endif


