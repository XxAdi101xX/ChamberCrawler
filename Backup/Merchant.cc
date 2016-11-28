#include <vector>
#include "Merchant.h"
//#include "GoldPile.h"
#include "Defines.cc"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

class Character;
class GoldPile;

extern bool merchantsAngered;


Merchant::Merchant(int wallet): Character{MERCHANT_HP_MAX, MERCHANT_HP,
        MERCHANT_ATTACK_VALUE, MERCHANT_DEFENCE_VALUE, false, Race::Merchant, wallet} {}


void Merchant::doStartTurnRoutine() {
	// makes merchant hostile if
	// player has killed a merchant before
        if (merchantsAngered) {
                this->setHostile();
        }
	
}


void Merchant::deathRoutine() {
        vector<Cell*> neighbourHood
                = (this->getCurrentCell())->getNeighbours();

        int numberOfGoldPilesAlreadyDropped = 0;


        for (auto neighbour : neighbourHood) {
                // if there is no item on a neighbouring cell
                if (!(neighbour->getItem)) {
                        neighbour->setItem(
                                make_shared<GoldPile>
                                (MERCHANT_DROPPED_GOLD_PILE_VALUE));
			
			++numberOfGoldPilesAlreadyDropped;
                }

                if (numberOfGoldPilesAlreadyDropped
                        == MERCHANT_NUMBER_OF_GOLD_PILES_DROPPED) {
                        return;
                }

        }

	merchantsAngered = true;
}


