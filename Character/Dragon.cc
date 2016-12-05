#include <vector>
#include "Dragon.h"
#include "../Messaging/Messaging.h"
#include "../Enumerations/Race.h"
#include "../Defines/Defines.h"
#include "../Items/GoldPile.h"
#include "../Cell/Cell.h"
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
	static_pointer_cast<GoldPile>((this->dragonHoardCell)->getItem())->unbind();
}


void Dragon::doStartTurnRoutine(Generator& rng) {
	// gets all neighbours of the dragonHoard
	vector<shared_ptr<Cell>> neighbourhood = (this->dragonHoardCell)->getNeighbours();

	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		shared_ptr<Character> occupant = neighbour->getOccupant();

		if (occupant && occupant->getPlayerState()) {
			this->setHostile();

			// attackes player if they are next to dragon hoard
			this->attack(*occupant, rng);

			// throws so that the program know the dragon already
			// attacked
			throw 1;
		}

	}


	// gets all neighbours of dragon
	neighbourhood = (this->getCurrentCell())->getNeighbours();

	// note that I would not like to repeat this code,
	// but there's no operator+ for vectors so I have
	// to check them seperately instead of together

	// check if they have a player on them
	for (auto neighbour: neighbourhood) {
		shared_ptr<Character> occupant = neighbour->getOccupant();

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
