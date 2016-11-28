#ifndef _TROLL_H_
#define _TROLL_H_

#include "Character.h"


class Troll final: public Character {
private:
        // overrides to add health
        virtual void doEndTurnRoutine() override;

public:
	Troll(int wallet);

};


#endif


