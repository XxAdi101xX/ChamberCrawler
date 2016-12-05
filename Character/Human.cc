#include <vector>
#include "Human.h"
#include "../Items/GoldPile.h"
#include "../Defines/Defines.h"
#include "../Cell/Cell.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;
class GoldPile;


// Human does not give gold on death, hence wallet field is set to 0
Human::Human(int wallet): Character{HUMAN_HP_MAX, HUMAN_HP,
	HUMAN_ATTACK_VALUE, HUMAN_DEFENCE_VALUE, true, Race::Human, 0} {}


void Human::deathRoutine() {
	vector<shared_ptr<Cell>> neighbourHood
		= (this->getCurrentCell())->getNeighbours();

	int numberOfGoldPilesAlreadyDropped = 0;


	for (auto neighbour : neighbourHood) {
		// if there is no item or character on a neighbouring cell
		if (neighbour && !(neighbour->getItem()) && !(neighbour->getOccupant())
            && neighbour->getCellType() == CellType::FloorTile) {
			
			neighbour->setItem
				(make_shared<GoldPile>(HUMAN_DROPPED_GOLD_PILE_VALUE));

			++numberOfGoldPilesAlreadyDropped;
		}

		if (numberOfGoldPilesAlreadyDropped
			== HUMAN_NUMBER_OF_GOLD_PILES_DROPPED) {

			return;
		}

	}

}
