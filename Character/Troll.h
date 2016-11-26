#ifndef _TROLL_H_
#define _TROLL_H_

#include <Character.h>


class Troll final: public Character {
public:
	// overrides to add health
	virtual void endTurnRoutine() override;
	virtual void setStats() override; // set Troll stats

};


#endif


