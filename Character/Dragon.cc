#include <vector>
#include "Dragon.h"
#include "Messaging.h"
#include "Race.h"
using namespace std;

class Character;


Dragon::Dragon(int wallet): Character{150, 150, 20, 20, false, Race::Dragon, wallet} {}


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


void Dragon::setDragonHoardCell(Cell* dragonHoardCell) {
	this->dragonHoardCell = dragonHoardCell;
}


