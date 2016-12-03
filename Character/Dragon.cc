#include <vector>
#include "Dragon.h"
#include "Messaging.h"
#include "Race.h"
#include "Defines.cc"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;


// Dragon does not give gold on death, hence wallet field is set to 0
Dragon::Dragon(int wallet): Character{DRAGON_HP_MAX, DRAGON_HP,
	DRAGON_ATTACK_VALUE, DRAGON_DEFENCE_VALUE,
	false, Race::Dragon, 0} {}


void Dragon::doMove(Direction direction) {/* does not move */}


void Dragon::deathRoutine() {
	// unbinds dragon hoard
	((this->dragonHoardCell)->getItem())->unbind();
}


void Dragon::doStartTurnRoutine(Generator& rng) {
	// gets all neighbours of the dragonHoard
	vector<Cell*> neighbourhood = (this->dragonHoardCell)->getNeighbours();

	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		Character* occupant = neighbour->getOccupant();

		if (occupant && occupant->getPlayerState()) {
			this->setHostile();

			// attackes player if they are next to dragon hoard
			this->attack(*occupant, rng);

			// throws so that the program know the dragon already
			// attacked
			throw;
		}

	}


	// gets all neighbours of dragon
	neighbourhood = (this->getCurrentCell())->getNeighbours();

	// note that I would not like to repeat this code,
	// but there's no operator+ for vectors so I have
	// to check them seperately instead of together

	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		Character* occupant = neighbour->getOccupant();

		if (occupant && occupant->getPlayerState()) {
			this->setHostile();
			// don't attack because dragon
			// will get to attack later
		}

	}

}


void Dragon::setDragonHoardCell(std::shared_ptr<Cell> dragonHoardCell) {
	this->dragonHoardCell = dragonHoardCell;
}
