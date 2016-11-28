#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "Character.h"


class Dragon final: public Character {
private:
	Cell* dragonHoardCell; // the cell with the dragonHoard on it

        // overrides move to do nothing
        virtual void doMove(Direction direction) override;

        // checks whether or not to turn hostile
        virtual void doStartTurnRoutine() override;

        // unbinds the dragon hoard
        virtual void deathRoutine() override;


public:
	Dragon(int wallet); // ctor
	
	// sets the dragonHoardCell field
	void setDragonHoardCell(Cell* dragonHoardCell);
};


#endif


