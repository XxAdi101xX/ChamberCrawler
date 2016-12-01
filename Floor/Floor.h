#ifndef __FLOOR_H__
#define __FLOOR_H__

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include "../Item/Item.h"
#include "../Cell/Cell.h"
#include "../TextDisplay/TextDisplay.h"


class Floor {
private:
    std::vector<std::vector<std::shared_ptr<Cell>>> theFloor;
    std::shared_ptr<TextDisplay> theDisplay;

    std::vector<int> floorDimensions;

    bool dfsSearch(std::shared_ptr<std::map<std::string>> travelled, const std::vector<int> curr,
        const std::vector<int> dest);

    std::string coordsToString(std::vector<int> coord);

public:

    Floor(std::shared_ptr<TextDisplay>);

    void initialize();
    void clearFloor();

    bool sameChamber(const std::vector<int> coords1, const std::vector<int> coords2) const;

    std::shared_ptr<Cell> getCell(const std::vector<int> coords) const;
    std::vector<int> getFloorDimensions() const;

};

std::istream &operator>>(std::istream &in, const Floor &floor);

#endif