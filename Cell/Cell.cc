#include "Cell.h"
#include "../Localisation/Localisation.cc"
using namespace std;

// constructor
Cell::Cell(){}

  void setCellType(CellType type);
  void setCoords(std::vector<Cell*> coords); sets coordinates of cell
  void addNeighbour(Cell* neighbour); // adds neighbour to neighbours vector
  void setItem(std::shared_ptr<Item> item); // adds item on cell
  void setOccupant(Character* occupant); // sets character on cell
  CellType getCellType(); // returns cell type
  std::vector<int> getCoords();
  std::shared_ptr<Item> getItem();
  Cell* getNeighbour(Direction direction); // returns neighbour in specified
                                           // direction
  std::vector<Cell*>& getNeighbours(); // returns refernce to vector with Cell*
  Character* getOccupant(); // return any characters occupying the cell

// returns an Info struct with information on cell
Info getInfo() {
	Info cellInfo;
	cellInfo.coordinates = this->coordinates;
	if (getOccupant() != nullptr) {
		if (occupant->getPlayerState() == true) {
			cellInfo.displayChar = '@';
		}
		else {
			string charName = occupant->getName();
			switch(charName) {
				case NAME_HUMAN: cellInfo.displayChar = 'H';
				case NAME_DWARF: cellInfo.displayChar = 'W';
				case NAME_ELF: cellInfo.displayChar = 'E';
				case NAME_ORC: cellInfo.displayChar = 'O';
				case NAME_MERCHANT: cellInfo.displayChar = 'M';
				case NAME_DRAGON: cellInfo.displayChar = 'D';
				case NAME_HALFLING: cellInfo.displayChar = 'L';
			}
		}
	}
	else if (item != nullptr) {
		if (item->getItemType == Item::GoldPile) {
			cellInfo.displayChar = ITEM_GOLD_PILE;
		}
		else if (item->getItemType == Item::Potion) {
			cellInfo.displayChar = ITEM_POTION;
		}
	}
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
		
	}
}

// Notifying the visual display whenever a change to the cell occurs  
void Cell::notify(Subject& whoNotified) {
	notifyObservers();
}
