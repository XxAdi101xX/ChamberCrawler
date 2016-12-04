#include <string>
#include "Cell.h"
#include "../Localisation/Localisation.h"
#include "../Info/Info.h"
using namespace std;

// constructor
Cell::Cell():
	neighbours {std::vector<shared_ptr<Cell>>(8)}
	{}

// Sets the Cell's type
void Cell::setCellType(CellType type) {
	this->cellType = type;
	this->notifyObservers();
}

// Sets coordinates of cell
void Cell::setCoords(std::vector<int> coords) {
	this->coordinates = coords;
}

// Adds neighbour to cell's neighbours vector
void Cell::addNeighbour(std::shared_ptr<Cell> neighbour) {
	std::vector<int> coords = neighbour->getCoords();
	if (coords[0] < coordinates[0] && coords[1] < coordinates[1]) {
		neighbours[1] = neighbour;
	}
	else if (coords[0] < coordinates[0] && coords[1] > coordinates[1]) {
		neighbours[7] = neighbour;
	}
	else if (coords[0] < coordinates[0]) {
		neighbours[0] = neighbour;
	}
	else if (coords[0] > coordinates[0] && coords[1] < coordinates[1]) {
		neighbours[3] = neighbour;
	}
	else if (coords[0] > coordinates[0] && coords[1] > coordinates[1]) {
		neighbours[5] = neighbour;
	}
	else if (coords[0] > coordinates[0]) {
		neighbours[4] = neighbour;
	}
	else if (coords[1] > coordinates[1]) {
		neighbours[6] = neighbour;
	}
	else {
		neighbours[2] = neighbour;
	}
}

// Adds item to cell
void Cell::setItem(shared_ptr<Item> item) {
	this->item = item;
	this->notifyObservers();
}

// Sets occupant of cell to the argument given
void Cell::setOccupant(shared_ptr<Character> occupant) {
	this->occupant = occupant;
	this->notifyObservers();
}

// Returns cell type
CellType Cell::getCellType() const {
	if (this == nullptr) return CellType::Null;
	return cellType;
}

// Returns the coordinates of the cell
vector<int> Cell::getCoords() const {
	return coordinates;
}

// Returns the item on the cell
shared_ptr<Item> Cell::getItem() const {
	return item;
}

// Returns the cell's neighbours in the specified direction
shared_ptr<Cell> Cell::getNeighbour(Direction direction) const {
	// The neighbours are always placed in a particular order in the vector
	if (direction == Direction::North) {
		return (getNeighbours()[0]);
	}
	else if (direction == Direction::NorthWest) {
		return (getNeighbours()[1]);
	}
	else if (direction == Direction::West) {
		return (getNeighbours()[2]);
	}
	else if (direction == Direction::SouthWest) {
		 return (getNeighbours()[3]);
	}
	else if (direction == Direction::South) {
		return (getNeighbours()[4]);
	}
	else if (direction == Direction::SouthEast) {
		return (getNeighbours()[5]);
	}
	else if (direction == Direction::East) {
		return (getNeighbours()[6]);
	}
	else {
		return (getNeighbours()[7]); // NorthEast
	}
}

// Returns a refernce to vector with all neighbouring Cells
vector<shared_ptr<Cell>> Cell::getNeighbours() const {
	return neighbours;
}

// Returns any character object occupying the cell or nullptr otherwise
std::shared_ptr<Character> Cell::getOccupant() const {
	return occupant;
}

// returns an Info struct with information on cell
Info Cell::getInfo() const {

	Info cellInfo;

	cellInfo.coordinates = this->coordinates;
	// check if cell occupies a character
	if (getOccupant() != nullptr) {
		if (occupant->getPlayerState() == true) {
			cellInfo.displayChar = CHAR_PLAYER;
		}
		else {
			string name = occupant->getName();
			if (name == NAME_HUMAN) {
				cellInfo.displayChar = CHAR_HUMAN;
			}
			else if (name == NAME_DWARF) {
				cellInfo.displayChar = CHAR_DWARF;
			}
			else if (name ==  NAME_ELF) {
				cellInfo.displayChar = CHAR_ELF;
			}
			else if (name == NAME_ORC) {
				 cellInfo.displayChar = CHAR_ORC;
			}
			else if (name == NAME_MERCHANT) {
				 cellInfo.displayChar = CHAR_MERCHANT;
			}
			else if (name == NAME_DRAGON) {
				cellInfo.displayChar = CHAR_DRAGON;
			}
			else if (name == NAME_HALFLING) {
				cellInfo.displayChar = CHAR_HALFLING;
			}
		}
	}
	// check if cell occupies an item
	else if (item != nullptr) {
		if (item->getItemType() == ItemType::GoldPile) {
			cellInfo.displayChar = CHAR_ITEM_GOLD_PILE;
		}
		else if (item->getItemType() == ItemType::Potion) {
			cellInfo.displayChar = CHAR_ITEM_POTION;
		}
	}
	// next few statements check for the remaining types of cells
	else if (getCellType() == CellType::Passage){
		cellInfo.displayChar = CHAR_PASSAGE;
	}
	else if (getCellType() == CellType::DoorWay) {
		cellInfo.displayChar = CHAR_DOOR_WAY;
	}
	else if (getCellType() == CellType::FloorTile) {
		cellInfo.displayChar = CHAR_FLOOR_TILE;
	}
	else if (getCellType() == CellType::Null) {
		cellInfo.displayChar = CHAR_NULL;
	}
	else if (getCellType() == CellType::Stairs) {
		cellInfo.displayChar = CHAR_STAIRS;
	}
	else if (getCellType() == CellType::Wall) {
		// check what type of wall is occupied by cell
		if ((((getNeighbour(Direction::East))->getCellType() != CellType::Null) &&
				((getNeighbour(Direction::West))->getCellType() != CellType::Null)) &&
				(((getNeighbour(Direction::East))->getCellType() == CellType::Wall) ||
				((getNeighbour(Direction::West))->getCellType() == CellType::Wall) ||
				((getNeighbour(Direction::West))->getCellType() == CellType::Stairs) ||
				((getNeighbour(Direction::East))->getCellType() == CellType::Stairs)))
																																						{
			cellInfo.displayChar = CHAR_HORIZONTAL_WALL;
		}
		else {
			cellInfo.displayChar = CHAR_VERTICAL_WALL;
		}
	}

	cellInfo.isCellInfo = true;

	return cellInfo;
}
