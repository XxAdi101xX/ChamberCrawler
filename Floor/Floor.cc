#include "Floor.h"
#include <string>
#include <map>
#include <utility>
#include "../Cell/Cell.h"
#include "../Enumerations/CellType.h"

Floor::Floor(std::shared_ptr<TextDisplay> td):
    theFloor {std::vector<std::vector<std::shared_ptr<Cell>>>()},
    theDisplay {td},
    floorDimensions {std::vector<int>()},
    floorNumber {1}
    {
    }

void Floor::initialize() {
    clearFloor();

    //theDisplay = std::make_shared<TextDisplay>(floorDimensions);
    theDisplay->setGridSize(floorDimensions);


    for (int i = 0; i < floorDimensions[0]; ++i) {
        for (int j = 0; j < floorDimensions[1]; ++j) {
            if (i > 0) {
                theFloor[i][j]->addNeighbour(theFloor[i - 1][j]);
            }
            if (j > 0) {
                theFloor[i][j]->addNeighbour(theFloor[i][j - 1]);
            }
            if (i + 1 < floorDimensions[0]) {
                theFloor[i][j]->addNeighbour(theFloor[i + 1][j]);
            }
            if (j + 1 < floorDimensions[1]) {
                theFloor[i][j]->addNeighbour(theFloor[i][j + 1]);
            }
            if (i > 0 && j > 0) {
                theFloor[i][j]->addNeighbour(theFloor[i- 1][j - 1]);
            }
            if (i > 0 && j + 1 < floorDimensions[1]) {
                theFloor[i][j]->addNeighbour(theFloor[i - 1][j + 1]);
            }
            if (i + 1 < floorDimensions[0] && j > 0) {
                theFloor[i][j]->addNeighbour(theFloor[i + 1][j - 1]);
            }
            if (i + 1 < floorDimensions[0] && j + 1 < floorDimensions[1]) {
                theFloor[i][j]->addNeighbour(theFloor[i + 1][j + 1]);
            }
            theFloor[i][j]->attach(theDisplay);

            //Just so it triggers neighbor events
            theFloor[i][j]->setCellType(theFloor[i][j]->getCellType());
        }
    }
}

void Floor::resetFloorNumber() {
    floorNumber = 1;
}

int Floor::getFloorNumber() {
    return floorNumber;
}

void Floor::clearFloor() {
    for (auto &row: theFloor) {
        for (auto &c: row) {
            CellType type = c->getCellType();
            std::vector<int> coords = c->getCoords();
//LOOK BACK
            c = std::make_shared<Cell>();
            c->setCoords(coords);
            c->setCellType(type);
        }
    }
}

bool Floor::sameChamber(const std::vector<int> coords1, const std::vector<int> coords2) const {
    return dfsSearch(std::map<std::string, bool>(), coords1, coords2);
}

//LOOK BACK
bool Floor::dfsSearch(std::map<std::string, bool> travelled, const std::vector<int> curr, const std::vector<int> dest) const {
    std::vector<std::shared_ptr<Cell>> neighbourCells = theFloor[curr[0]][curr[1]]->getNeighbours();

    if (curr.size() != 2 && dest.size() != 2) return false;

    if (curr[0] == dest[0] && curr[1] == dest[1]) return true;

    for (auto &c: neighbourCells) {
        if (travelled.count(coordsToString(c->getCoords()))) {
            travelled[coordsToString(c->getCoords())] = true;
            if (dfsSearch(travelled, c->getCoords(), dest)) return true;
        }
    }
    return false;
}

std::string Floor::coordsToString(std::vector<int> coord) const {
    return std::to_string(coord[0]) + " " + std::to_string(coord[1]);
}


std::shared_ptr<Cell> Floor::getCell(const std::vector<int> coords) const {
    return theFloor[coords[0]][coords[1]];
}

std::vector<int> Floor::getFloorDimensions() const {
    return floorDimensions;
}


std::istream &operator>>(std::istream &in, Floor &f) {

    f.theFloor = std::vector<std::vector<std::shared_ptr<Cell>>>();

    while (!in.eof()) {
        std::string row;
        std::getline(in, row);
        if (row == "") break;

        f.theFloor.push_back(std::vector<std::shared_ptr<Cell>>());
        for (auto r: row) {
            std::shared_ptr<Cell> cell = std::make_shared<Cell>();
            cell->setCoords(std::vector<int>{static_cast<int>(f.theFloor.size()) - 1, static_cast<int>(f.theFloor.back().size())});
            switch (r) {
                case '|':
                    cell->setCellType(CellType::Wall);
                    break;
                case '-':
                    cell->setCellType(CellType::Wall);
                    break;
                case '+':
                    cell->setCellType(CellType::DoorWay);
                    break;
                case '#':
                    cell->setCellType(CellType::Passage);
                    break;
                case ' ':
                    cell->setCellType(CellType::Null);
                    break;
				case '\\':
                    cell->setCellType(CellType::Stairs);
                    break;
                default:
                    cell->setCellType(CellType::FloorTile);
                    break;
            }

            f.theFloor.back().push_back(std::move(cell));
        }
    }

    f.floorDimensions = std::vector<int>{static_cast<int>(f.theFloor.size()), static_cast<int>(f.theFloor[0].size())};

/*
    for (int i = 0; i < f.floorDimensions[0]; ++i) {
            std::cout << "Size: " << i << " " << f.theFloor[i].size() << endl;
            for (int j = 0; j < f.floorDimensions[1]; ++j) {
                std::cout << f.theFloor[i][j]->getCoords().size() << endl;
                std::cout << f.theFloor[i][j].use_count() << endl;
            }
    }
    */
    f.initialize();


    return in;
}
