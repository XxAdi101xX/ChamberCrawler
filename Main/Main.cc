#include <iostream>
#include <string>>
#include "Localisation.cc"
using namespace std;

int main() {
	// game global variables
	TextDisplay theTextDisplay = TextDisplay{};
	int floorCount = 1;
	Floor currentFloor = Floor{&theTextDisplay};
	bool merchantsAngered = false;
	vector<PotionType> usedPotions;
	shared_ptr<Character> player = nullptr;

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
				cout << "You have selected" << " " 
					<< SHADE_NAME << endl;
				player = createCharacter(Race::Shade);			
				break;

			case CMD_DROW_SELECT :
				cout << RACE_SELECTION_MESSAGE << " " 
					<< DROW_NAME << endl;
				player = createCharacter(Race::Drow);
				break;

                	case CMD_VAMPIRE_SELECT :
                        	cout << "You have selected" << " "
                                	<< VAMPIRE_NAME << endl;
                        	player = createCharacter(Race::Vampire);
                        	break;

                	case CMD_GOBLIN_SELECT :
                       		cout << "You have selected" << " "
                                	<< GOBLIN_NAME << endl;
                        	player = createCharacter(Race::Goblin;
                        	break;

                	case CMD_TROLL_SELECT :
                        	cout << "You have selected" << " "
                	                << TROLL_NAME << endl;
        	                player = createCharacter(Race::Troll);
	                        break;

			default :
				cout << INVALID_CMD_MSG << endl;
	
		}

	}

newLevelStart:
	if (floorCount = NUMBER_OF_FLOORS) {
		cout << GAME_CLEARED_MSG << endl;
		cout << FINAL_SCORE_MSG << ": " << player.getScore() << endl;
		cout <<	"(" << CMD_YES << "|" << CMD_NO << ")    " 
			<< REPLAY_PROMPT << endl;

		while (true) {
			if (!(cin >> cmd) || cmd == CMD_QUIT || CMD_NO) {
				cout << GOODBYE_MSG << endl;
				return 0;
			}

			else if (cmd == CMD_YES) {
				// clear game data

				goto titleScreen;
			}

			else {
				cout << INVALID_CMD_MSG << endl;
			}

		}

	}

	cout << LOADING_MSG << endl;

	floor.initialize();
	


}
