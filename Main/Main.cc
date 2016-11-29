#include <iostream>
#include <string>
#include <vector>
#include "Generator.h"
#include "Floor.h"
#include "Character.h"
#include "Localisation.cc"
#include "MainHelpers.cc"
using namespace std;


int main(int argc, char *argv[]) {
	// game global variables
	Generator rng = Generator{};
	TextDisplay theTextDisplay = TextDisplay{};
	int floorCount = 0;
	Floor currentFloor = Floor{&theTextDisplay};

	bool NPCMovementPaused = false;	
	bool merchantsAngered = false;
	vector<PotionType> usedPotions;

	// generation variables
	shared_ptr<Character> player = nullptr;
	vector<int> playerCoords;

	vector<int> stairCoords;

	// counters and temporaries
	vector<shared_ptr<Character>> alreadyActed;
	Cell* tempCell;
	vector<Cell*> tempNeighbourhood;
	shared_ptr<Character> tempCharacter;
	shared_ptr<Character> tempDefender;

	vector<int> tempCoords;

	vector<int> dragonCoords;

	bool playerHasActed;

	// number of attempts made to find valid neighbour
	int neighbourAttemptsCounter = 0;

	int numberOfSpawnedPotions = 0;
	PotionType tempPotionType;

	int numberOfSpawnedGoldPiles = 0;
	int tempGoldPileValue;

	int numberOfSpawnedNPCs = 0;
	Race tempRace;
	int tempWallet;

	string cmd;


titleScreen:
	cout << "Welcome to CC3K" << endl;
	cout << "Please pick one of the following races" << endl;

	cout << "(" << CMD_SHADE_SELECT << ")    " << SHADE_NAME << endl;
	cout << "(" << CMD_DROW_SELECT << ")    " << DROW_NAME << endl;
	cout << "(" << CMD_VAMPIRE_SELECT << ")    " << VAMPIRE_NAME << endl;
	cout << "(" << CMD_GOBLIN_SELECT << ")    " << GOBLIN_NAME << endl;
	cout << "(" << CMD_TROLL_SELECT << ")    " << TROLL_NAME << endl;

	while (!player) {
		if (!(cin >> cmd) || cmd == CMD_QUIT) {
			cout << GOODBYE_MSG << endl;
			return 0;
		}

		switch(cmd) {
			case CMD_SHADE_SELECT :
				cout << "You have selected" << " " << SHADE_NAME << endl;
				player = createCharacter(Race::Shade);			
				break;

			case CMD_DROW_SELECT :
				cout << RACE_SELECTION_MESSAGE << " " << DROW_NAME << endl;
				player = createCharacter(Race::Drow);
				break;

			case CMD_VAMPIRE_SELECT :
				cout << "You have selected" << " " << VAMPIRE_NAME << endl;
				player = createCharacter(Race::Vampire);
				break;

			case CMD_GOBLIN_SELECT :
				cout << "You have selected" << " " << GOBLIN_NAME << endl;
				player = createCharacter(Race::Goblin);
				break;

			case CMD_TROLL_SELECT :
				cout << "You have selected" << " " << TROLL_NAME << endl;
				player = createCharacter(Race::Troll);
				break;

			case CMD_RESTART :
				goto titleScreen;

			default :
				cout << INVALID_CMD_MSG << endl;
	
		}

	}

// attaches player to display so we can report what
// happened to the player
player.attach(&theTextDisplay);


newFloorStart:
	// updates floor count since this is a new floor
	++floorCount;

	// checks for win
	while (floorCount > NUMBER_OF_FLOORS) {
		cout << GAME_CLEARED_MSG << endl;
		cout << FINAL_SCORE_MSG << ": " << player.getScore() << endl;
		cout <<	"(" << CMD_YES << "|" << CMD_NO << ")    " 
		<< REPLAY_PROMPT << endl;

		if (!(cin >> cmd) || cmd == CMD_QUIT || CMD_NO) {
			cout << GOODBYE_MSG << endl;
			return 0;
		}

		else if (cmd == CMD_YES || cmd == CMD_RESTART) {
			// clear game data
			// NEED TO COMPLETE...........................................	
			goto titleScreen;
		}

		else {
			cout << INVALID_CMD_MSG << endl;
		}

	}

	cout << LOADING_MSG;

	currentFloor.initialize();

	// generate player location
	// gets proper coordinates for player	
	playerCoords = getValidCoords();

	// gets the cell at playerCoords
	tempCell = currentFloor.getCell(playerCoords);

	// sets the player in place
	// cell also gets set occupant
	player.setCell(tempCell);

	// sets the player character as the player
	player.setPlayer();

	// informs player of progress in loading
	cout << PERIOD;

	// generate stairs location
	// gets a proper coordinates for stairs
	do {
		stairCoords = getValidCoorDS();

		// reroll if coordinates are in the same chamber as player
	} while(currentFloor.sameChamber(playerCoords, stairCoords));

	temp

	// sets the stairs in place
	currentFloor.getCell(stairCoords)->setCellType(CellType::Stairs);

	cout << PERIOD;

	// generates potions
	while (numberOfSpawnedPotions < POTION_SPAWN_NUMBER) {
		// gets proper cell
		tempCell = getValidCell();

		// gets a random PotionType
		tempPotionType = rng.genPotionType();

		// adds a potion to the cell
		tempCell->setItem(make_shared<Potion>(tempPotionType));

		++numberOfSpawnedPotions;
	}
	
	cout << PERIOD;

		// generates gold
		while (numberOfSpawnedGoldPiles < GOLD_PILE_SPAWN_NUMBER) {
		// gets proper coordinates
		tempCoords = getValidCoords();

		// gets the cell at tempCoords
		tempCell = currentFloor.getCell(tempCoords);

		// gets a random GoldPile value
		tempGoldPileValue = rng.genGold();

		// if the gold spawned was a dragon hoard
		if (tempGoldValue == GOLD_PILE_DRAGON_HOARD_VALUE) {
			try {
				// get a valid neighbouring coordinate
				dragonCoords = getValidNeighbourCoordinates(tempCoords);

				// get a dragon
				tempCharacter = createCharacter(Race::Dragon);

				// sets dragon in place
				tempCharacter->setCell(tempCell);

				// gives it it's cell
				tempCharacter
					->setDragonHoardCell(tempCell);

			}

			catch {
				// remove the pile added
				tempCell->setItem(nullptr);

				// decrements counter to allow second try
				--numberOfSpawnedGoldPiles;

			}

		}

				// not a merchant hoard, not a dragon hoard
				else if (tempGoldValue != GOLD_PILE_MERCHANT_HOARD_VALUE) {
					tempCell->setItem(make_shared<GoldPile>(tempGoldPileValue));
				}

		// is actually a merchant hoard
		else {
			// decrements counter to allow second try
			--numberOfSpawnedGoldPiles;
		}

		++numberOfSpawnedGoldPiles;
		}

	cout << PERIOD;

	// generates enemies
		while (numberOfSpawnedNPCs < NPC_SPAWN_NUMBER) {
		// gets a proper cell
		tempCell = getValidCell();

		// gets a random Race
		tempRace = rng.genNPCRace();

		// gets a random NPC
		tempCharacter = createCharacter(tempRace);

		// sets NPC in place
		tempCharacter->setCell(tempCell);

		++numberOfSpawnedNPCs;
		}

	cout << FINISH_PAST_TENSE << endl;


	// game start

	while (player.getHP() > 0) {
		// plater turn start
		player.startTurnRoutine();

		while (!(playerHasActed)) {
			playerHasActed = true; // default value

			if (!(cin >> cmd) || cmd == CMD_QUIT) {
				cout << GOODBYE_MSG << endl;
				return 0;
			}

			switch(cmd) {
				case CMD_MOVE_NORTH :
					break;

				case CMD_MOVE_SOUTH :
					break;

				case CMD_MOVE_EAST :
					break;

				case CMD_MOVE_WEST :
					break;

				case CMD_MOVE_NORTH_EAST :
					break;

				case CMD_MOVE_NORTH_WEST :
					break;

				case CMD_MOVE_SOUTH_EAST :
					break;

				case CMD_MOVE_SOUTH_WEST :
					break;

				case CMD_USE :
					break;

				case CMD_ATTACK :
					break;

				case CMD_STOP :
					break;

				case CMD_RESTART :
					// clears data
					// TO BE IMPLEMENTED ......................................................
					break;

				default :
					// invalid command

					// makes sure to wait for player cmd
					playerHasActed = false;
		}

		player.endTurnRoutine();


		// NPC turn start
		for (int i = 0; 
			i < (currentFloor->getFloorDimension())[0]; ++i) {
			for (int j = 0; 
				j < (currentFloor->getFloorDimension())[1]; 
				++j) {

				// gets the all necessary info for this cell
				tempCell = currentFloor.getCell(vector{i,j});
				tempCharacter = tempCell->getOccupant();
				tempNeighbourhood = tempCell->getNeighbours();

				if (tempCharacter && !(tempCharacter->getPlayerState())) {
					try {
						// dragon may attack player during startTurnRoutine
						// if they are next to dragon hoard
						// will throw if so
						tempCharacter->startTurnRoutine();
					}

					catch {
						// caught dragon attacking
						alreadyActed.emplace_back(tempCharacter);
					}

					for (auto neighbour: tempNeighbourhood) {
						// checks if already acked
						if (hasActed(tempCharacter)) {
							break;
						}

						tempDefender = neighbour->getOccupant();

						// if player is beside NPC,// and NPC is hostile
						if (tempDefender->getPlayerState() 
							&& tempCharacter->getHostileState()) {

							tempCharacter->attack(*tempDefender, rng);

							// logs the attacker
							alreadyActed.emplace_back(tempCharacter);
							break;
						}

					}

					if (!(hasActed(tempCharacter) && !NPCMovementPaused)) {
						try {
							tempCharacter->move(getValidDirection);
						}

						catch{}

						// logs the character 
						// than just moved
						alreadyActed.emplace_back(tempCharacter);
					}

					tempCharacter->endTurnRoutine();

					// report updates to theTextDisplay
					tempCharacter->notifyObservers();
								}

				// report updates to theTextDisplay
				tempCell->notifyObservers();

			}

		}

		// clears logged NPCs
		alreadyActed.erase();

		// report updates to theTextDisplay
		player.notifyObserver();

		// outputs the new game state
		cout << theTextDisplay << endl;
	}


	// game over
	while (player.getHP() <= 0) {
		cout << GAME_OVER_MSG << end;
		cout << FINAL_SCORE_MSG << ": " << player.getScore() << endl;
		cout << "(" << CMD_YES << "|" << CMD_NO << ")    " 
		<< REPLAY_PROMPT << endl;

		if (!(cin >> cmd) || cmd == CMD_QUIT || CMD_NO) {
			cout << GOODBYE_MSG << endl;
			return 0;
		}

		else if (cmd == CMD_YES || cmd == CMD_RESTART) {
			// clear game data
			// NEED TO COMPLETE...........................................
			goto titleScreen;	
		}

		else {
				cout << INVALID_CMD_MSG << endl;
		}

	}

}



