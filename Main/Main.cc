#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <ctime>

// Observer/Subject pattern
#include "../ObserverSubject/Subject.h"
#include "../ObserverSubject/Observer.h"
#include "../Info/Info.h"

// basic game elements
#include "../Generator/Generator.h"
#include "../Floor/Floor.h"
#include "../Cell/Cell.h"

// displays
#include "../TextDisplay/TextDisplay.h"

// Character and subclasses
#include "../Character/Character.h"
#include "../Character/Shade.h"
#include "../Character/Drow.h"
#include "../Character/Vampire.h"
#include "../Character/Troll.h"
#include "../Character/Goblin.h"
#include "../Character/Human.h"
#include "../Character/Dwarf.h"
#include "../Character/Elf.h"
#include "../Character/Orc.h"
#include "../Character/Merchant.h"
#include "../Character/Dragon.h"
#include "../Character/Halfling.h"

// Item and subclasses
#include "../Items/Item.h"
#include "../Items/GoldPile.h"
#include "../Items/Potion.h"

// enumerations
#include "../Enumerations/Direction.h"
#include "../Enumerations/Race.h"
#include "../Enumerations/ItemType.h"
#include "../Enumerations/PotionType.h"
#include "../Enumerations/CellType.h"


// Other .h files
#include "../Defines/Defines.h"
#include "../Localisation/Localisation.h"
#include "MainHelpers.h"
using namespace std;


int main(int argc, char *argv[]) {
	// default seed
	int seed = time(NULL);

	ifstream file;

	string filename;

	bool readFromFile = false;

	if (argc > 3) {
		cerr << ERR_INVALID_NUMBER_OF_CMD_LINE_ARGS << endl;
		cerr << ERR_USAGE << endl;
		return 1;
	}

	else if (argc == 3) {
		string test;

		try {
			file.open(argv[1]);
			test = file.peek();
			filename = argv[1];
			readFromFile = true;
		}

		catch (...) {
			cerr << ERR_BAD_FILE << endl;
			return 2;
		}

		try {
			seed = stoi(argv[2]);
		}

		catch (...) {
			cerr << ERR_BAD_SEED << endl;
			return 3;
		}

	}

	else if (argc == 2) {
		string test;

	    try {
			file.open(argv[1]);
            test = file.peek();
			filename = argv[1];
			readFromFile = true;
        }

        catch (...) {
        	try {
            	seed = stoi(argv[1]);
        	}

        	catch (invalid_argument a) {
            	cerr << ERR_BAD_CMD_LINE_ARG << endl;
            	return 4;
        	}

        }


	}

	// game global variables
	Generator rng {seed};
	int floorCount = 0;
	Floor currentFloor {shared_ptr<TextDisplay>(&theTextDisplay)};
	TextDisplay theTextDisplay {};

	bool NPCMovementPaused = false;
	bool merchantsAngered = false;
	vector<PotionType> usedPotions;

	// generation variables
	shared_ptr<Character> player = nullptr;
	vector<int> playerCoords;

	vector<int> stairCoords;


	// generation variables, counters and temporaries
	vector<int> floorDimensions {DEFAULT_FLOOR_WIDTH, DEFAULT_FLOOR_LENGTH};

	char tempChar;

	bool playerHasBeenPlaced = false;

	// two stacks are utilized to link dragon hoards with dragons
	vector<shared_ptr<Cell>> dragonHoardCellStack;
	vector<shared_ptr<Dragon>> dragonStack;

	vector<shared_ptr<Character>> alreadyActed;
	shared_ptr<Cell> tempCell;
	vector<shared_ptr<Cell>> tempNeighbourhood;
	shared_ptr<Character> tempCharacter;
	shared_ptr<Dragon> tempDragon;
	shared_ptr<Character> tempDefender;

	vector<int> tempCoords;

	vector<int> dragonCoords;

	bool playerHasActed = false;

	int numberOfSpawnedPotions = 0;
	PotionType tempPotionType;

	int numberOfSpawnedGoldPiles = 0;
	int tempGoldPileValue;

	int numberOfSpawnedNPCs = 0;
	Race tempRace;

	shared_ptr<Item> tempItem;

	string cmd;


titleScreen:
	cout << MSG_WELCOME << endl;
	cout << PROMPT_RACE_SELECTION << endl;

	cout << "(" << CMD_SHADE_SELECT << ")    " << NAME_SHADE << endl;
	cout << "(" << CMD_DROW_SELECT << ")    " << NAME_DROW << endl;
	cout << "(" << CMD_VAMPIRE_SELECT << ")    " << NAME_VAMPIRE << endl;
	cout << "(" << CMD_GOBLIN_SELECT << ")    " << NAME_GOBLIN << endl;
	cout << "(" << CMD_TROLL_SELECT << ")    " << NAME_TROLL << endl;

	// while player is not yet set
	while (!player) {
		if (!(cin >> cmd) || cmd == CMD_QUIT) {
			cout << MSG_GOODBYE << endl;
			return 0;
		}

		else if (cmd == CMD_SHADE_SELECT) {
			cout << MSG_RACE_SELECTED << " " << NAME_SHADE << endl;
			player = createCharacter(Race::Shade);
		}

		else if (cmd == CMD_DROW_SELECT) {
			cout << MSG_RACE_SELECTED << " " << NAME_DROW << endl;
			player = createCharacter(Race::Drow);
		}

		else if (cmd == CMD_VAMPIRE_SELECT) {
			cout << MSG_RACE_SELECTED << " " << NAME_VAMPIRE << endl;
			player = createCharacter(Race::Vampire);
		}

		else if (cmd == CMD_GOBLIN_SELECT) {
			cout << MSG_RACE_SELECTED << " " << NAME_GOBLIN << endl;
			player = createCharacter(Race::Goblin);
		}

		else if (cmd == CMD_TROLL_SELECT) {
			cout << MSG_RACE_SELECTED << " " << NAME_TROLL << endl;
			player = createCharacter(Race::Troll);
		}

		else if	(cmd == CMD_RESTART) {
			goto titleScreen;
		}

		else {
			cerr << ERR_INVALID_CMD << endl;
		}

	}


	// attaches player to display so we can report what
	// happened to the player
	player->attach(shared_ptr<Observer>(static_cast<Observer *>(&theTextDisplay)));


newFloorStart:
	// updates floor count since this is a new floor
	++floorCount;

	player->clearBuffs();

	// checks for win
	while (floorCount > NUMBER_OF_FLOORS) {
		cout << MSG_GAME_CLEAR << endl;
		cout << MSG_FINAL_SCORE << ": " << player->getScore() << endl;
		cout <<	"(" << CMD_YES << "|" << CMD_NO << ")    "
		<< PROMPT_REPLAY << endl;

		if (!(cin >> cmd) || cmd == CMD_QUIT || cmd == CMD_NO) {
			cout << MSG_GOODBYE << endl;
			return 0;
		}

		else if (cmd == CMD_YES || cmd == CMD_RESTART) {
			cout << MSG_RESETTING << endl;

			// clear game data
			reset();

			goto titleScreen;
		}

		else {
			cerr << ERR_INVALID_CMD << endl;
		}

	}

	cout << MSG_LOADING;

	if (readFromFile) {
		try {
			file >> currentFloor;
		}

		// for errors reading the map
		catch (...) {
			cerr << ERR_BAD_MAP << endl;
			return 5;
		}

		// reinitialize the file to scan for objects on the floor
		file.close();
		file.open(filename);

		// skips previous floors in the file
		file.ignore((floorCount - 1)
			* floorDimensions[0] * floorDimensions[1]);

		floorDimensions = currentFloor.getFloorDimensions();

		tempCoords = vector<int>{0,0};

		while (file.get(tempChar)) {
			tempCell = currentFloor.getCell(tempCoords);
			tempCharacter.reset();
			tempDragon.reset();
			tempItem.reset();

			switch(tempChar) {
				case CHAR_READ_POTION_RESTORE_HEALTH :
					//tempItem.reset(new Potion{PotionType::RestoreHealth});
					tempItem = make_shared<Potion>(PotionType::RestoreHealth);
					break;

                case CHAR_READ_POTION_POISON_HEALTH :
					tempItem = make_shared<Potion>(PotionType::PoisonHealth);
                    break;

                case CHAR_READ_POTION_BOOST_ATTACK :
					tempItem = make_shared<Potion>(PotionType::BoostAttack);
                    break;

                case CHAR_READ_POTION_BOOST_DEFENCE :
					tempItem = make_shared<Potion>(PotionType::BoostDefence);
                    break;

                case CHAR_READ_POTION_WOUND_ATTACK :
					tempItem = make_shared<Potion>(PotionType::WoundAttack);
                    break;

                case CHAR_READ_POTION_WOUND_DEFENCE :
					tempItem = make_shared<Potion>(PotionType::WoundDefence);
                    break;

                case CHAR_READ_GOLD_PILE_NORMAL :
					tempItem = make_shared<GoldPile>(GOLD_PILE_NORMAL_VALUE);
                    break;

                case CHAR_READ_GOLD_PILE_SMALL :
					tempItem = make_shared<GoldPile>(GOLD_PILE_SMALL_VALUE);
                    break;

                case CHAR_READ_GOLD_PILE_MERCHANT_HOARD :
					tempItem
						= make_shared<GoldPile>
						(GOLD_PILE_MERCHANT_HOARD_VALUE);
                    break;

                case CHAR_READ_GOLD_PILE_DRAGON_HOARD :
					tempItem
						= make_shared<GoldPile>
						(GOLD_PILE_DRAGON_HOARD_VALUE);

					// adds dragon hoard cell to stack for linking
					dragonHoardCellStack.emplace_back(tempCell);
                    break;

                case CHAR_PLAYER :
					// prevents placing the player twice
					if (playerHasBeenPlaced) {
						cerr << ERR_BAD_MAP << endl;
						return 5;
					}

					tempCharacter = player;
					playerHasBeenPlaced = true;
                    break;

                case CHAR_HUMAN :
				 	tempCharacter = createCharacter(Race::Human);
					//tempCharacter = createCharacter(Race::Human);
                    break;

                case CHAR_DWARF :
					tempCharacter = createCharacter(Race::Dwarf);
                    break;

                case CHAR_ELF :
					tempCharacter = createCharacter(Race::Elf);
                    break;

                case CHAR_ORC :
					tempCharacter = createCharacter(Race::Orc);
                    break;

                case CHAR_MERCHANT :
					tempCharacter = createCharacter(Race::Merchant);
                    break;

                case CHAR_DRAGON :
					tempDragon = static_pointer_cast<Dragon>(createCharacter(Race::Dragon));

					// adds dragon to stack for linking
					dragonStack.emplace_back(tempDragon);
                    break;

                case CHAR_HALFLING :
					tempCharacter = createCharacter(Race::Halfling);
                    break;

				default : ;
					// do nothing

			}

			// if an Item was read, place the item
			if (tempItem) {
				tempCell->setItem(tempItem);
			}

			// if an Character was read, place the character
			else if (tempCharacter) {
				tempCharacter->setCell(tempCell);
			}

			// special case due to typing differences
			// MAY FIX LATER WITH CASTING......................................
			else if (tempDragon) {
				tempDragon->setCell(tempCell);
			}

			// handling dragon and dragon hoards
			if (dragonStack.size() > 0
				&& dragonHoardCellStack.size() > 0) {

				// cell that the dragon hoard is on
				tempCell = dragonHoardCellStack.back();

				// the dragon
				tempDragon = dragonStack.back();

				// links the two above
				tempDragon->setDragonHoardCell(tempCell);

				// removes the two since their generation
				// is complete
				dragonStack.pop_back();
				dragonHoardCellStack.pop_back();

			}

			// advancing the coordinate

			// if at end of line
			if (tempCoords[2] == floorDimensions[2] - 1) {
				tempCoords = vector<int>{tempCoords[1] + 1, 0};
			}

			// normal traversal
			else {
				tempCoords = vector<int>{tempCoords[1], tempCoords[2] + 1};
			}

		}

		// if we have unlinked dragons or dragon hoard cells
		if (dragonStack.size() != 0 || dragonHoardCellStack.size() != 0) {
				cerr << ERR_BAD_MAP << endl;
				return 5;
		}

	}

	else {
		currentFloor.initialize(floorDimensions);

		floorDimensions = currentFloor.getFloorDimensions();

		// generate player location
		// gets proper coordinates for player
		playerCoords = getValidCoords();

		// gets the cell at playerCoords
		tempCell = currentFloor.getCell(playerCoords);

		// sets the player in place
		// cell also gets set occupant
		player->setCell(tempCell);

		// sets the player character as the player
		player->setPlayer();

		playerHasBeenPlaced = true;

		// informs player of progress in loading
		cout << PERIOD;

		// generate stairs location
		// gets a proper coordinates for stairs
		do {
			stairCoords = getValidCoords();

			// reroll if coordinates are in the same chamber as player
		} while(currentFloor.sameChamber(playerCoords, stairCoords));

		// sets the stairs in place
		currentFloor.getCell(stairCoords)->setCellType(CellType::Stairs);

		cout << PERIOD;

		// generates potions
		while (numberOfSpawnedPotions < SPAWN_NUMBER_POTION) {
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
		while (numberOfSpawnedGoldPiles < SPAWN_NUMBER_GOLD_PILE) {

			// gets proper coordinates
			tempCoords = getValidCoords();

			// gets the cell at tempCoords
			tempCell = currentFloor.getCell(tempCoords);

			// gets a random GoldPile value
			tempGoldPileValue = rng.genGold();

			// if the gold spawned was a dragon hoard
			if (tempGoldPileValue == GOLD_PILE_DRAGON_HOARD_VALUE) {
				try {
					// get a valid neighbouring coordinate
					dragonCoords = getValidNeighbourCoordinates(tempCoords);

					// get a dragon
					tempDragon = static_pointer_cast<Dragon>(createCharacter(Race::Dragon));

					// sets dragon in place
					tempDragon->setCell(tempCell);

					// gives it it's cell
					tempDragon
						->setDragonHoardCell(tempCell);

				}

				// if all neighbours are occupied
				catch (...) {
					// remove the pile added
					tempCell->setItem(nullptr);

					// decrements counter to allow second try
					--numberOfSpawnedGoldPiles;

				}

			}

			// not a merchant hoard, not a dragon hoard
			else if (tempGoldPileValue != GOLD_PILE_MERCHANT_HOARD_VALUE) {
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
		while (numberOfSpawnedNPCs < SPAWN_NUMBER_NPC) {
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

	}

	cout << MSG_LOADING_COMPLETE << endl;

	// outputs game state
	outputGameState();

	// game start

	while (player->getHP() > 0) {
		// player turn start
		playerHasActed = false;

		try {
			player->startTurnRoutine(rng);
		}

		// if the startTurnRoutine forced the character to act
		// note that normall this doesnt happen
		catch (...) {
			playerHasActed = true;
		}

		while (!(playerHasActed)) {
			playerHasActed = true; // default result

			if (!(cin >> cmd) || cmd == CMD_QUIT) {
				cout << MSG_GOODBYE << endl;
				return 0;
			}

			else if (cmd == CMD_NORTH) {
				player->move(Direction::North);
			}

			else if (cmd == CMD_SOUTH) {
				player->move(Direction::South);
			}

			else if (cmd == CMD_EAST) {
				player->move(Direction::East);
			}

			else if (cmd == CMD_WEST) {
				player->move(Direction::West);
			}

			else if (cmd == CMD_NORTH_EAST) {
				player->move(Direction::NorthEast);
			}

			else if (cmd ==	CMD_NORTH_WEST) {
				player->move(Direction::NorthWest);
			}

			else if (cmd == CMD_SOUTH_EAST) {
				player->move(Direction::SouthEast);
			}

			else if (cmd == CMD_SOUTH_WEST) {
				player->move(Direction::SouthWest);
			}

			else if	(cmd == CMD_USE) {
				playerHasActed = false;

				while (!playerHasActed) {
					playerHasActed = true; // default result

					if (!(cin >> cmd) || cmd == CMD_QUIT) {
						cout << MSG_GOODBYE << endl;
						return 0;
					}

	               	else if (cmd == CMD_NORTH) {
						tempCell = (currentFloor.getCell(playerCoords))->getNeighbour(Direction::North);
					}

           	    	else if (cmd == CMD_SOUTH) {
						tempCell = (currentFloor.getCell(playerCoords))
                          	->getNeighbour(Direction::South);
             	    }

					else if (cmd == CMD_EAST) {
                   		tempCell = (currentFloor.getCell(playerCoords))
                        	->getNeighbour(Direction::East);
					}

					else if (cmd == CMD_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::West);
					}

					else if (cmd == CMD_NORTH_EAST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::NorthEast);
					}

					else if (cmd == CMD_NORTH_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::NorthWest);
					}

					else if (cmd == CMD_SOUTH_EAST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::SouthEast);
					}

					else if (cmd == CMD_SOUTH_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::SouthWest);
					}

					else {
						// invalid direction
						cerr << ERR_INVALID_DIRECTION << endl;

						// makes sure to wait for player cmd
						playerHasActed = false;
					}

					// if valid command was issued
					if (playerHasActed) {
						// gets the item on cell
						tempItem = tempCell->getItem();

						// if there is actually an item, use it
						if (tempItem) {
							player->applyItem(tempItem);

							tempCell->setItem(nullptr);
						}

						// otherwise pretend it was invalid commmand
						else {
							//invalid direction
							cerr << ERR_INVALID_DIRECTION << endl;

							// makes sure to wait for player cmd
							playerHasActed = false;
						}

					}

				}

			}

			else if (cmd == CMD_ATTACK) {
				playerHasActed = false;

				while (!playerHasActed && cin >> cmd) {
					playerHasActed = true; // default result

					if (cmd == CMD_NORTH) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::North);
					}

					else if (cmd == CMD_SOUTH) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::South);
					}

					else if (cmd == CMD_EAST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::East);
					}

					else if (cmd == CMD_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::West);
					}

					else if (cmd == CMD_NORTH_EAST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::NorthEast);
					}

					else if (cmd == CMD_NORTH_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::NorthWest);
					}

					else if (cmd == CMD_SOUTH_EAST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::SouthEast);
					}

					else if (cmd == CMD_SOUTH_WEST) {
						tempCell = (currentFloor.getCell(playerCoords))
							->getNeighbour(Direction::SouthWest);
					}

					else {
						// invalid direction
						cerr << ERR_INVALID_DIRECTION << endl;

						// makes sure to wait for player cmd
						playerHasActed = false;
					}

					// if valid command was issued
					if (playerHasActed) {
						// gets the cell occupant
						tempDefender = tempCell->getOccupant();

						// if occupant acutally exits
						if (tempDefender) {
							player->attack(*tempDefender, rng);
						}

						// otherwise pretend it was invalid command
						else {
							// invalid direction
							cerr << ERR_INVALID_DIRECTION << endl;

							// makes sure to wait for player cmd
							playerHasActed = false;
						}

					}

				}

			}

			else if (cmd == CMD_STOP) {
				NPCMovementPaused = true;
			}

			else if (cmd == CMD_RESTART) {
				cout << MSG_RESETTING << endl;

				// clears data
				reset();

				goto titleScreen;
			}

			else {
					// invalid command
					cerr << ERR_INVALID_CMD << endl;

					// makes sure to wait for player cmd
					playerHasActed = false;
			}

		}

		player->endTurnRoutine();

		// reports updates to observers
		player->notifyObservers();

		// need to update coordinates that main has
		playerCoords = (player->getInfo()).coordinates;

		// checks for moving to new floor
		if (playerCoords == stairCoords) {
			goto newFloorStart;
		}


		// outputs new game state
		outputGameState();

		// NPC turn start
		for (int i = 0; i < (currentFloor.getFloorDimensions())[0]; ++i) {
			for (int j = 0; j < (currentFloor.getFloorDimensions())[1]; ++j) {

				// gets the all necessary info for this cell
				tempCell = currentFloor.getCell(vector<int>{i,j});
				tempCharacter = tempCell->getOccupant();
				tempNeighbourhood = tempCell->getNeighbours();

				if (tempCharacter && !(tempCharacter->getPlayerState())) {
					try {
						// dragon may attack player during startTurnRoutine
						// if they are next to dragon hoard
						// will throw if so
						tempCharacter->startTurnRoutine(rng);
					}

					// if caught dragon attacking because player
					// was next to dragon hoard
					catch (...) {
						alreadyActed.emplace_back(tempCharacter);
					}

					for (auto neighbour: tempNeighbourhood) {
						// checks if already acked
						if (hasActed(tempCharacter)) {
							break;
						}

						if (neighbour) {
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

					}

					if (!(hasActed(tempCharacter) && !NPCMovementPaused)) {
						try {
							tempCharacter
								->move(getValidMove(vector<int>{i,j}));
						}

						// failure to move because neighbouring cells
						// are occupied
						catch (...) {}

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
		alreadyActed.clear();

		// report updates to observer
		player->notifyObservers();

		// for DLC purposes (e.g. knockback)
		playerCoords = (player->getInfo()).coordinates;

		// checks for moving on to new floor
        if (playerCoords == stairCoords) {
            goto newFloorStart;
        }

		// outputs the new game state
		outputGameState();
	}


	// game over
	while (player->getHP() <= 0) {
		cout << MSG_GAME_OVER << endl;
		cout << MSG_FINAL_SCORE << ": " << player->getScore() << endl;
		cout << "(" << CMD_YES << "|" << CMD_NO << ")    "
		<< PROMPT_REPLAY << endl;

		if (!(cin >> cmd) || cmd == CMD_QUIT || cmd == CMD_NO) {
			cout << MSG_GOODBYE << endl;
			return 0;
		}

		else if (cmd == CMD_YES || cmd == CMD_RESTART) {
			cout << MSG_RESETTING << endl;

			// clear game data
			reset();

			goto titleScreen;
		}

		else {
				cerr << ERR_INVALID_CMD << endl;
		}

	}

}
