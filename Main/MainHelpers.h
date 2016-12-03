#ifndef __MAINHELPER_H__
#define __MAINHELPER_H__

#include <vector>
#include <iostream>
#include <memory>


using namespace std;

class Generator;
class Floor;
class TextDisplay;

extern Generator rng;
extern Floor currentFloor; // note that floor is cleared at initialization
extern TextDisplay theTextDisplay;
extern vector<int> floorDimensions;



// globals that need to be reset
extern int floorCount;
extern bool NPCMovementPaused;
extern bool merchantsAngered;
extern vector<PotionType> usedPotions;
extern shared_ptr<Character> player;
extern bool playerHasBeenPlaced;
extern vector<shared_ptr<Character>> alreadyActed;
extern bool playerHasActed;
extern int numberOfSpawnedPotions;
extern int numberOfSpawnedGoldPiles;
extern int numberOfSpawnedNPCs;

bool isValidCoordinates(vector<int> coord);
bool isOccupied(vector<int> coord);
vector<int> getValidCoords();
vector<int> getValidNeighbourCoordinates(vector<int> base);
bool hasActed(shared_ptr<Character> character);
Direction getValidMove(vector<int> base);
int getNormalOrSmallGoldPile ();
shared_ptr<Character> createCharacter(Race race);
void reset();
void outputGameState();


#endif
