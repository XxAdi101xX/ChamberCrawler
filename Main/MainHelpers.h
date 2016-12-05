#ifndef __MAINHELPER_H__
#define __MAINHELPER_H__

#include <vector>
#include <iostream>
#include <memory>
#include "../Enumerations/PotionType.h"
#include "../Enumerations/Race.h"


class Character;
class Cell;
enum class Direction;
class Generator;
class Floor;
class TextDisplay;

extern Generator rng;
extern std::shared_ptr<TextDisplay> theTextDisplay;
extern Floor currentFloor; // note that floor is cleared at initialization

extern std::vector<int> floorDimensions;

// globals that need to be reset
extern int floorCount;
extern bool NPCMovementPaused;
extern bool merchantsAngered;
extern std::vector<PotionType> usedPotions;
extern std::shared_ptr<Character> player;
extern bool playerHasBeenPlaced;
extern std::vector<std::shared_ptr<Character>> alreadyActed;
extern bool playerHasActed;
extern int numberOfSpawnedPotions;
extern int numberOfSpawnedGoldPiles;
extern int numberOfSpawnedNPCs;

std::shared_ptr<Cell> getValidCell();
bool isValidCoordinates(std::vector<int> coord);
bool isOccupied(std::vector<int> coord);
std::vector<int> getValidCoords();
std::vector<int> getValidNeighbourCoordinates(std::vector<int> base);
bool hasActed(std::shared_ptr<Character> character);
Direction getValidMove(std::vector<int> base);
int getNormalOrSmallGoldPile ();
std::shared_ptr<Character> createCharacter(Race race);
void reset();
void outputGameState();


#endif
