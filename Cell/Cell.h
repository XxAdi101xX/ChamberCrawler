#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>
#include <memory>
#include <vector>
#include "../Enumerations/CellType.h"
#include "../Enumerations/Direction.h"
#include "../Enumerations/ItemType.h"
#include "../Character/Character.h"
#include "../ObserverSubject/Subject.h"
#include "../Items/Item.h"

using namespace std;

struct Info;

class Cell final: public Subject {
	CellType cellType; // type of cell (eg. wall, stairway ...)
	std::vector<int> coordinates; // coordinates of the cell
	std::vector<shared_ptr<Cell>> neighbours; // all neighbouring cells
	std::shared_ptr<Item> item = nullptr;
	std::shared_ptr<Character> occupant = nullptr;
 public:
	Cell(); // Constructor

	void setCellType(CellType type);
	void setCoords(std::vector<int> coords); // sets coordinates of the cell
	void addNeighbour(std::shared_ptr<Cell> neighbour); // adds neighbour to neighbours vector
	void setItem(std::shared_ptr<Item> item); // adds item on cell
	void setOccupant(std::shared_ptr<Character> occupant); // sets character on cell

	CellType getCellType() const; // returns cell type
	std::vector<int> getCoords() const;
	std::shared_ptr<Item> getItem() const;
	shared_ptr<Cell> getNeighbour(Direction direction) const; // returns neighbour in specified
																					 // direction
	std::vector<shared_ptr<Cell>> getNeighbours() const; // returns refernce to vector with Cell*
	std::shared_ptr<Character> getOccupant() const; // return any characters occupying the cell
	Info getInfo() const; // returns an Info struct with information on cell
};

#endif
