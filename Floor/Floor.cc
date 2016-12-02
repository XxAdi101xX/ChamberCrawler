#include "Floor.h"
#include <string>
#include <map>
#include "../Cell/Cell.h"
#include "../Enumerations/CellType.h"

Floor::Floor(std::shared_ptr<TextDisplay> td):
    theFloor {std::vector<std::vector<std::shared_ptr<Cell>>>()},
    theDisplay {td},
    floorDimensions {std::vector<int>()}
    {}

void Floor::initialize() {
    clearFloor();

    for (int i = 0; i < floorDimensions[0]; ++i) {
        for (int j = 0; j < floorDimensions[1]; ++j) {
            if (i > 0) {
                theDisplay[i][j].addNeighbour(theDisplay[i - 1][j]);
            }
            if (j > 0) {
                theDisplay[i][j].addNeighbour(theDisplay[i][j - 1]);
            }
            if (i + 1 < floorDimensions[0]) {
                theDisplay[i][j].addNeighbour(theDisplay[i + 1][j]);
            }
            if (j + 1 < floorDimensions[1]) {
                theDisplay[i][j].addNeighbour(theDisplay[i][j + 1]);
            }
            floorDimensions[i][j].attach(theDisplay);
        }
    }
}

void Floor::clearFloor() {
    for (auto &row: theFloor) {
        for (auto &c: row) {
            CellType type = c.getCellType();
//LOOK BACK
            c = *(std::make_shared<Cell>());
            c.setCellType(type);
        }
    }
}

bool Floor::sameChamber(const std::vector<int> coords1, const std::vector<int> coords2) const {
    return bfsSearch(std::shared_ptr<std::map<std::string, bool>>(), coords1, coords2);
}

//LOOK BACK
bool Floor::dfsSearch(std::shared_ptr<std::map<std::string, bool>> travelled, const std::vector<int> curr, const std::vector<int> dest) {
    std::vector<std::shared_ptr<Cell>> neighbourCells = theFloor[currentCoord[0]][currentCoord[1]].getNeighbours();

    if (curr.size() != 2 && dest.size() != 2) return false;

    if (curr[0] == dest[0] && curr[1] == dest[1]) return true;

    for (auto &c: neighbourCells) {
        if (travelled.count(coordsToString(c.getCoords()))) {
            travelled[coordsToString(c.getCoords())] = true;
            if (dfsSearch(travelled, c, dest)) return true;
        }
    }
    return false;
}

std::string coordsToString(std::vector<int> coord) {
    return std::to_string(coord[0]) + " " + std::to_string(coord[1]);
}


std::shared_ptr<Cell> Floor::getCell(const std::vector<int> coords) const {
    return theFloor[coords[0]][coords[1]];
}

std::vector<int> Floor::getFloorDimensions() const {
    return floorDimensions;
}


std::istream &operator>>(std::istream &in, const Floor &floor) {
    while (!in.eof()) {
        std::string row;
        in >> row;

        theFloor.emplace_back(std::vector<std::shared_ptr<Cell>>());

        std::shared_ptr<Cell> cell = std::make_shared<Cell>();

        for (auto r: row) {
            switch (r) {
                case '|':
                    cell.setCellType(CellType::Wall);
                    break;
                case '-':
                    cell.setCellType(CellType::Wall);
                    break;
                case '+':
                    cell.setCellType(CellType::Doorway);
                    break;
                case '#':
                    cell.setCellType(CellType::Passage);
                    break;
                case '.':
                    cell.setCellType(CellType::FloorTile);
                    break;
                case ' ':
                    cell.setCellType(CellType::Null);
                    break;
                default:
                    break;
            }

            theFloor.back.emplace_back(cell);
        }
    }
    floorDimensions = std::vector<int>{theFloor.size(), theFloor[0].size()}
    return in;
}
