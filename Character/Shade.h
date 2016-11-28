#ifndef _SHADE_H_
#define _SHADE_H_

#include "Character.h"


class Shade final: public Character {
private:
	// overrides to give a 50% score bonus
        virtual int getScoreBonus() const override;

public:
	Shade(int wallet);

};


#endif


