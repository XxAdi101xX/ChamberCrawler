#ifndef _DROW_H_
#define _DROW_H_

#include "Character.h"
class Potion;


class Drow final: public Character {
private:
	// overrides the normal addHPViaPotion
	// to amplify effects by 50% 
	virtual void addHPViaPotion(int amount) override;
	
	// add 50% to potion effects
	virtual int getAttackBuffBonus() const override;
	
	// add 50% to potion effects
	virtual int getDefenceBuffBonus() const override;

public:
	Drow(int wallet); // ctor

};


#endif


