#include <vector>
#include <memory>
#include "Floor.h"
#include "Direction.h"
#include "Defines.cc"
using namespace std;

extern Generator rng;
extern Floor currentFloor;
extern vector<shared_ptr<Character>> alreadyActed;



// checks if coordinates given is a FloorTile or not
bool isValidCoordinates(vector<int> coord) {
	return (currentFloor.getCell(coord))->getCellType() 
		== CellType::FloorTile ? true : false;
}


// checks if coordinates given has an Item or Character on it
bool isOccupied(vector<int> coord) {
	return (currentFloor.getCell(coord))->getOccupant()
		|| (currentFloor.getCell(coord)->getItem()) 
		? true : false;
}


// wrapper for generator that only returns a valid coordinate
vector<int> getValidCoordinates() {
	// safety check no necessary assuming there is enough room for spawning

        do {
                vector<int> tempCoordinates = rng.genCoordinate();

                // reroll if coordinates are not for a FloorTile
                // or has an occupant already
        } while (!(isValidCoordinates(tempCoordinates))
		|| isOccupied(tempCoordinates));

	return tempCoordinates;
}


// wrapper for generator that only returns a valid neighbouring coordinate
// given a base coordinate
// throws if all neighbours are not valid
vector<int> getValidNeighbourCoordinates(vector<int> base) {
	// safety check
	vector<vector<int>> checkedCoordinates

	do {
                vector<int> tempCoordinates = rng.genNeighbourCoord(base);

		bool checked = false;

                // checks if neighbour was logged
		for (auto coordinates: checkedCoordinates) {
                        if (coordinates == tempCoordinates) {
                                checked = true;
                                break;
                        }
                }

		// if neighbour was not logged, log it
                if (!(checked)) {
                        checkedCoordinates.emplace_back(tempCoordinates);
                }

		// checks if all neighbours were tried
                if (checkedCoordinates.size() == DIRECTION_ENUMERATION) {
                        // no valid neighbour
			throw;
                }

                // reroll if coordinates are not for a FloorTile
                // or has an occupant already
        } while (!(isValidCoordinates(tempCoordinates))
                || isOccupied(tempCoordinates));

        return tempCoordinates;

}


bool hasActed(shared_ptr<Character> character) {
	for (auto actedCharacter: alreadyActed) {
		if (actedCharacter == character) {
			return true;
		}

	}

	return false;
}


// wrapper for generator that only returns a valid direction to move to
// given the current coordinate
// throws if no valid move exists
Direction getValidMove(vector<int> base) {
	// safety check
	vector<Direction>  checkedDirections;

	do {
		tempDirection = rng.genDirection();
		vector<int> tempCoordinates 
			= (base->getNeighbour(tempDirection))->getCoord();

		bool checked = false;

		// checks if this direction has been logged
		for (auto direction: checkedDirections) {
			if (direction == tempDirection) {
				checked = true;
				break;
			}
		}

		// if directions was not logged, log it
		if (!(checked)) {
			checkedDirections.emplace_back(tempDirection);
		}

		// checks if all directions were tried
		if (checkedDirections.size() == DIRECTION_ENUMERATION) {
			// no valid move
			throw;
		}

		// reroll if cell in direction is not a FloorTile
		// or has an occupant already
	} while (!(isValidCoordinates(tempCoordinates))
                || isOccupied(tempCoordinates));

	return tempDirection;
}


// wrapper for generator that only produces a small or 
// normal amount of gold as described by defines.cc
int getNormalOrSmallGoldPile () {
	do {
		int tempAmount = rng.genGold();

		// reroll if value is not small or not normal
	} while (tempAmount != GOLD_PILE_SMALL_VALUE 
		|| tempAmount != GOLD_PILE_NORMAL_VALUE);

	return tempAmmount;
}


