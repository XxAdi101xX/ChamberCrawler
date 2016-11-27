#include <vector>
#include "Dragon.h"
using namespace std;

class Character;


void Dragon::move(Direction direction) {/* does not move */}


void Dragon::deathRoutine() {
	// unbinds dragon hoard
	((this->dragonHoardCell)->getItem())->unbind();
}


void Dragon::startTurnRoutine() {
	// gets all neighbours
	vector<Cell*> neighbourhood 
		= (this->getCurrentCell())->getNeighbours();
	
	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		Character* occupant = neighbour->getOccupant();

		if (occupant && occupant->getPlayerState()) {
			this->setHostile();
		}

	}

	// gets all neighbours of the dragonHoard
	neighbourhood = (this->dragonHoardCell)->getNeighbours();

	// note that I would not like to repeat this code,
	// but there's no operator+ for vectors so I have
	// to check them seperately instead of together

	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		Character* occupant = neighbour->getOccupant();

        	if (occupant && occupant->getPlayerState()) {
                	this->setHostile();
                }

        }

}


void Dragon::setStats() {
	this->setHPMax(150);
	this->setHP(150);
	this->setAttackValue(20);
	this->setDefenceValue(20);
	this->setHostile(false);
}


void Dragon::setDragonHoardCell(Cell* dragonHoardCell) {
	this->dragonHoardCell = dragonHoardCell;
}


