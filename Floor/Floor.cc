#include "Floor.h"
#include <string>
#include <map>
#include "../Cell/Cell.h"
#include "../Enumerations/CellType.h"

Floor::Floor(std::shared_ptr<TextDisplay> td):
    theFloor {std::vector<std::vector<std::shared_ptr<Cell>>>()},
    theDisplay {td},
    floorDimensions {std::vector<int>()},
    floorNumber {1}
    {}

void Floor::initialize() {
    clearFloor();

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
            theFloor[i][j]->attach(theDisplay);
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
//LOOK BACK
            c = std::make_shared<Cell>();
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

    while (!in.eof()) {
        std::string row;
        in >> row;

        f.theFloor.push_back(std::vector<std::shared_ptr<Cell>>());

        for (auto r: row) {
            std::shared_ptr<Cell> cell = std::make_shared<Cell>();
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
                case '.':
                    cell->setCellType(CellType::FloorTile);
                    break;
                case ' ':
                    cell->setCellType(CellType::Null);
                    break;
                default:
                    break;
            }

            f.theFloor.back().emplace_back(cell);
        }
    }
    f.floorDimensions = std::vector<int>{static_cast<int>(f.theFloor.size()), static_cast<int>(f.theFloor[0].size())};
    return in;
}
