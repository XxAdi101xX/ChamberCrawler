#include <vector>
#include <memory>
#include "Floor.h"
#include "Generator.h"
#include "TextDisplay.h"
#include "Character.h"
#include "Direction.h"
#include "Defines.cc"
using namespace std;

extern Generator rng;
extern Floor currentFloor; // note that floor is cleared at initialization
extern TextDisplay theTextDisplay;

// globals that need to be reset
extern int floorCount;
extern bool NPCMovementPaused;
extern bool merchantsAngered;
extern vector<PotionType> usedPotions;
extern shared_ptr<Character> player;
extern vector<shared_ptr<Character>> alreadyActed;
extern bool playerHasActed;
extern int numberOfSpawnedPotions;
extern int numberOfSpawnedGoldPiles;
extern int numberOfSpawnedNPCs;



// checks if coordinates given is a FloorTile or not
bool isValidCoordinates(vector<int> coord) {
	return (currentFloor.getCell(coord))->getCellType() 
		== CellType::FloorTile ? true : false;
}


// checks if coordinates given has an Item or Character on it
bool isOccupied(vector<int> coord) {
	return (currentFloor.getCell(coord))->getOccupant() 
	|| (currentFloor.getCell(coord)->getItem()) ? true : false;
}


// wrapper for generator that only returns a valid coordinate
vector<int> getValidCoords() {
	// safety check no necessary assuming there is enough room for spawning

	do {
		vector<int> tempCoordinates = rng.genCoordinate();

		// reroll if coordinates are not for a FloorTile
		// or has an occupant already
	} while (!(isValidCoordinates(tempCoordinates))
	|| isOccupied(tempCoordinates));

	return tempCoordinates;
}


// wrapper for getValidCoords that turns the coordinate to a Cell *
Cell* getValidCell() {
	return currentFloor.getCell(getValidCoords());
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
		if (checkedDirections.size() == DIRECTION_ENUMERATION {
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


// creates a character using the given race
shared_ptr<Character> createCharacter(Race race) {
	int tempWallet = getNormalOrSmallGoldPile();

	switch(race) {
		case Race::Shade : 
			return Shade(tempWallet);
		case Race::Drow : 
            return Drow(tempWallet);
		case Race::Vampire : 
            return Vampire(tempWallet);
		case Race::Troll : 
            return Troll(tempWallet);
		case Race::Goblin : 
            return Goblin(tempWallet);
		case Race::Human : 
            return Human(tempWallet);
		case Race::Dwarf : 
            return Dwarf(tempWallet);
		case Race::Elf : 
            return Elf(tempWallet);
		case Race::Orc : 
            return Orc(tempWallet);
		case Race::Merchant : 
            return Merchant(tempWallet);
		case Race::Dragon : 
            return Dragon(tempWallet);
		case Race::Halfling : 
            return Halfling(tempWallet);
	}

}


// resets all necessary global variables for new game
void reset() {
	floorCount = 0;

	NPCMovementPaused = false;
	merchantsAngered = false;

	usedPotions.erase();
	
	player = nullptr;
	
	alreadyActed.erase();
	
	playerHasActed = false;
	
	numberOfSpawnedPotions = 0;
	numberOfSpawnedGoldPiles = 0;
	numberOfSpawnedNPCs = 0;

}


// outputs the game state stored
// allows adding new displays easily
void outputGameState() {
	cout << theTextDisplay << endl;
}
