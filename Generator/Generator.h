#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "../Enumerations/Race.h"
#include "../Enumerations/PotionType.h"
#include "../Enumerations/Direction.h"

#include <vector>

class Generator {
    int seed;
public:
    Generator(int seed);

    Race genNPCRace();
    PotionType genPotionType();
    int genGold();
    bool genHitMiss();
    std::vector<int> genCoordinates(std::vector<int> size);
    Direction genDirection();
    std::vector<int> genNeighbourCoord(std::vector<int> base);

};

#endif
