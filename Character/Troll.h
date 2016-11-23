#include <Character.h>


class Troll final: public Character {
public:
	// overrides to add health
	virtual void endTurnRoutine() override;
	virtual void setStats() override; // set Troll stats

};


