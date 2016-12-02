#include "Cell.h"
#include "../Localisation/Localisation.cc"
using namespace std;

// constructor
Cell::Cell(){}

// Sets the Cell's type
void Cell::setCellType(CellType type) {
	this->cellType = type;
}

// Sets coordinates of cell   
void Cell::setCoords(std::vector<Cell*> coords) {
	this->coordinates = coords;
}

// Adds neighbour to cell's neighbours vector
void Cell::addNeighbour(Cell* neighbour) {
	neighbours.emplace_back(neighbour);
}
  
// Adds item to cell
void Cell::setItem(shared_ptr<Item> item) {
	this->item = item
}

// Sets occupant of cell to the argument given  
void Cell::setOccupant(Character* occupant) {
	this->occupant = occupant;
}
  
// Returns cell type
CellType Cell::getCellType() {
	return cellType;
}
  
// Returns the coordinates of the cell
vector<int> Cell::getCoords() {
	return coordinates;
}
  
// Returns the item on the cell
shared_ptr<Item> Cell::getItem() {
	return item;
}

// Returns the cell's neighbours in the specified direction  
Cell* Cell::getNeighbour(Direction direction) {
	switch (direction) {
		// The neighbours are always placed in a particular order in the vector
		case Direction::North : return (getNeighbours()[0]);
		case Direction::NorthWest : return (getNeighbours()[1]);
		case Direction::West : return (getNeighbours()[2]);
		case Direction::SouthWest : return (getNeighbours()[3]);
		case Direction::South : return (getNeighbours()[4]);
		case Direction::SouthEast : return (getNeighbours()[5]);
		case Direction::East : return (getNeighbours()[6]);
		case Direction::NorthEast : return (getNeighbours()[7]);	
	}
}
                                          
// Returns a refernce to vector with all neighbouring Cells
vector<Cell*>& Cell::getNeighbours() {
	return &neighbours;
}
  
// Returns any character object occupying the cell or nullptr otherwise
Character* Cell::getOccupant() {
	return occupant;
}

// returns an Info struct with information on cell
Info Cell::getInfo() {
	Info cellInfo;
	cellInfo.coordinates = this->coordinates;
	// check if cell occupies a character
	if (getOccupant() != nullptr) {
		if (occupant->getPlayerState() == true) {
			cellInfo.displayChar = CHAR_PLAYER;
		}
		else {
			switch(occupant->getName()) {
				case NAME_HUMAN : cellInfo.displayChar = CHAR_HUMAN;
				case NAME_DWARF : cellInfo.displayChar = CHAR_DWARF;
				case NAME_ELF : cellInfo.displayChar = CHAR_ELF;
				case NAME_ORC : cellInfo.displayChar = CHAR_ORC;
				case NAME_MERCHANT : cellInfo.displayChar = CHAR_MERCHANT;
				case NAME_DRAGON : cellInfo.displayChar = CHAR_DRAGON;
				case NAME_HALFLING : cellInfo.displayChar = CHAR_HALFLING;
			}
		}
	}
	// check if cell occupies an item
	else if (item != nullptr) {
		if (item->getItemType == ItemType::GoldPile) {
			cellInfo.displayChar = CHAR_ITEM_GOLD_PILE;
		}
		else if (item->getItemType == ItemType::Potion) {
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
	else if (getCellType == CellType::Wall) {
		// check what type of wall is occupied by cell
		if (((getNeighbour(Direction::West))->getCellType() == CellType::Wall) &&
				((getNeighbour(Direction::East))->getCellType() == CellType::Wall)) {
			cellInfo.displayChar = CHAR_HORIZONTAL_WALL;
		}
		else {
			cellInfo.displayChar = CHAR_VERTICAL_WALL;
		}
	}
	return cellInfo;
}

// Notifying the visual display whenever a change to the cell occurs  
void Cell::notify(Subject& whoNotified) {
	this->notifyObservers();
}

