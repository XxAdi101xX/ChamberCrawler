#include <vector>
#include "Human.h"
//#include "GoldPile.h"
using namespace std;

class Character;
class GoldPile

extern int normalGoldPileValue;
extern int numberOfGoldPilesDroppedByHuman;


Human::Human(int wallet): 
	Character{140, 140, 20, 20, true, Race::Human, wallet} {}


void Human::deathRoutine() {
	vector<Cell*> neighbourHood 
		= (this->getCurrentCell())->getNeighbours();

	int numberOfGoldPilesAlreadyDropped = 0;


	for (auto neighbour : neighbourHood) {
		// if there is no item on a neighbouring cell
		if (!(neighbour->getItem)) {
			neighbour->setItem(
				make_shared<GoldPile>(normalGoldPileValue));
		}

		if (numberOfGoldPilesAlreadyDropped 
			== numberOfGoldPilesDroppedByHuman) {
			return;
		}

	}

}


