#include <vector>
#include "Floor.h"
using namespace std;

extern Generator rng;
extern Floor currentFloor;


bool isValidCoordinates(vector<int> coord) {
	return (currentFloor.getCell(coord))->getCellType() 
		== CellType::FloorTile ? true : false
}

bool isOccupied(vector<int> coord) {
	return (currentFloor.getCell(coord))->getOccupant()
		|| (currentFloor.getCell(coord)->getItem()) 
		? true : false;
}

vector<int> getValidCoordinates() {
        do {
                vector<int> tempCoordinates = rng.genCoordinate();

                // reroll if coordinates are not for a FloorTile
                // or has an occupant already
        } while (!(isValidCoordinates(tempCoords))
		|| isOccupied(tempCoords));

	return tempCoordinates;
}
