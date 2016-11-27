#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "Character.h"


class Dragon final: public Character {
private:
	Cell* dragonHoardCell; // the cell with the dragonHoard on it
public:
	Dragon(int wallet); // ctor

	// overrides move to do nothing
	virtual void move(Direction direction) override;

	// checks whether or not to turn hostile
        virtual void startTurnRoutine() override;

	// unbinds the dragon hoard
	virtual void deathRoutine() override;
	
	// sets the dragonHoardCell field
	void setDragonHoardCell(Cell* dragonHoardCell);
};


#endif


