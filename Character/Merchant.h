#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "Character.h"


class Merchant final: public Character {
private:
        // overrides to check whether or not to turn hostile
        virtual void doStartTurnRoutine(Generator& rng) override;

        // overrides to drop merchant goldpile upon death
        virtual void deathRoutine() override;

public:
	Merchant(int wallet); // ctor

};


#endif


