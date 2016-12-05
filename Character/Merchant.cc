#include <vector>
#include "Merchant.h"
#include "../Items/GoldPile.h"
#include "../Defines/Defines.h"
#include "Character.h"
#include "../Items/GoldPile.h"
#include "../Cell/Cell.h"

using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc


extern bool merchantsAngered;


// Merchant does not give gold on death, hence wallet field is set to 0
Merchant::Merchant(int wallet): Character{MERCHANT_HP_MAX, MERCHANT_HP,
	MERCHANT_ATTACK_VALUE, MERCHANT_DEFENCE_VALUE, false, Race::Merchant, 0} {}


void Merchant::doStartTurnRoutine(Generator& rng) {
	// makes merchant hostile if
	// player has killed a merchant before
	if (merchantsAngered) {
		this->setHostile();
	}

	if (this->getHP() != MERCHANT_HP_MAX) {
		merchantsAngered = true;
		this->setHostile();
	}

}


void Merchant::deathRoutine() {
	vector<shared_ptr<Cell>> neighbourHood 
		= (this->getCurrentCell())->getNeighbours();

	int numberOfGoldPilesAlreadyDropped = 0;

	for (auto neighbour : neighbourHood) {
		// if there is no item or character on a neighbouring cell
		if (neighbour && !(neighbour->getItem()) && !(neighbour->getOccupant())
			&& neighbour->getCellType() == CellType::FloorTile) {

			neighbour->setItem
			(make_shared<GoldPile>(MERCHANT_DROPPED_GOLD_PILE_VALUE));

			++numberOfGoldPilesAlreadyDropped;
		}

		if (numberOfGoldPilesAlreadyDropped
			== MERCHANT_NUMBER_OF_GOLD_PILES_DROPPED) {

			return;
		}

	}

	merchantsAngered = true;
}
