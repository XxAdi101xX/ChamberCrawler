#include "Generator.h"
#include <cstdlib.h>
#include "../Defines/Defines.h"

Generator::Generator(int seed):
    seed {seed}
    {
        srand(seed);
    }

Race Generator::genNPCRace() {
    float r = (float)rand()/INT_MAX;

    r -= HUMAN_SPAWN_CHANCE;
    if (r > 0) {
        return Race::Human;
    }

    r-= DWARF_SPAWN_CHANCE;
    if (r > 0) {
        return Race::Dwarf;
    }

    r-= HALFLING_SPAWN_CHANCE;
    if (r > 0) {
        return Race::Halfling;
    }

    r -= ELF_SPAWN_CHANCE;
    if (r > 0) {
        return Race::Elf;
    }

    r-= ORC_SPAWN_CHANCE;
    if (r > 0) {
        return Race::Orc;
    }

    return Race::Merchant;
}

PotionType Generator::genPotionType() {
    return PotionType(rand()%6);
}

int Generator::genGold() {
    float r = (float)rand()/INT_MAX;

    r -= GOLD_PILE_SMALL_SPAWN_CHANCE;

    if (r > 0)
        return GOLD_PILE_SMALL_VALUE;

    r -= GOLD_PILE_NORMAL_SPAWN_CHANCE;

    if (r > 0)
        return GOLD_PILE_NORMAL_VALUE;

    return GOLD_PILE_DRAGON_HOARD_VALUE;
}

bool Generator::genHitMiss() {
    return (rand()%2 == 0);
}

std::vector<int> genCoordinates(std::vector<int> size) {
    return std::vector<int>{rand() % size[0], rand() % size[1]};
}


Direction genDirection() {
    return Direction(rand()%8)
}

std::vector<int> genNeighbourCoord(std::vector<int> base) {
    Direction d = genDirection();
    switch (d) {
        case Direction::North:
            ++base[0];
            break;
        case Direction::NorthEast:
            ++base[0];
            ++base[1];
            break;
        case Direction::East:
            ++base[1];
            break;
        case Direction::SouthEast:
            --base[0];
            ++base[1];
            break;
        case Direction::South:
            --base[0];
            break;
        case Direction::SouthWest:
            --base[0];
            --base[1];
            break;
        case Direction::West:
            --base[1];
            break;
        case Direction::NorthWest:
            ++base[0];
            --base[1];
            break;
        default:
            break;
    }
    return base;
}
