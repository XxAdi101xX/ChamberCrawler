#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "Character.h"


class Merchant final: public Character {
public:
	// overrides to check whether or not to turn hostile
	virtual void startTurnRoutine() override;

	// overrides to drop merchant goldpile upon death
        virtual void deathRoutine() override;
	virtual void setStats() override; // sets Merchant stats

};


#endif

