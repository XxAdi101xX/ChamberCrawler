

#include <string>

// commands
const std::string CMD_NORTH = "no";
const std::string CMD_SOUTH = "so";
const std::string CMD_WEST = "ea";
const std::string CMD_EAST = "we";
const std::string CMD_NORTH_EAST = "ne";
const std::string CMD_NORTH_WEST = "nw";
const std::string CMD_SOUTH_EAST = "se";
const std::string CMD_SOUTH_WEST = "sw";

const std::string CMD_USE = "u";
const std::string CMD_ATTACK = "a";

const std::string CMD_SHADE_SELECT = "s";
const std::string CMD_DROW_SELECT = "d";
const std::string CMD_VAMPIRE_SELECT = "v";
const std::string CMD_GOBLIN_SELECT = "g";
const std::string CMD_TROLL_SELECT = "t";

const string CMD_STOP = "f";
const string CMD_RESTART = "r";
const string CMD_QUIT = "q";

const string CMD_YES = "y";
const string CMD_NO = "n";

// messages
const string MSG_WELCOME = "Welcome to CC3k!";
const string MSG_GOODBYE = "Goodbye!";

const string MSG_GAME_CLEAR = "Game Cleared!";
const string MSG_GAME_OVER = "Game Over!";

const string MSG_RESETTING = "Resetting...";

const string MSG_LOADING = "Loading";
const string MSG_LOADING_COMPLETE = "Done!";

const string MSG_FINAL_SCORE = "Final score";

const string MSG_RACE_SELECTED = "You have selected";

// prompts
const string PROMPT_RACE_SELECTION = "Please select a race";
const string PROMPT_REPLAY = "Replay?";

// errors
const string ERR_INVALID_CMD = "Invalid command";
const string ERR_INVALID_DIRECTION = "Invalid direction";

const string ERR_USAGE = "Usage: cc3k [filename] [seed]";
const string ERR_INVALID_NUMBER_OF_CMD_LINE_ARGS 
	= "Invalid number of command line arguments";
const string ERR_BAD_FILE = "File does not exist or could not be read";
const string ERR_BAD_SEED = "Seed was not in the correct integer form";
const string ERR_BAD_CMD_LINE_ARG = "Invalid command line argument";
const string ERR_BAD_MAP = "The map read was invalid";

// vocab:

const string WORD_HP_NOUN = "HP";
const string WORD_ATTACK_NOUN = "attack";
const string WORD_BY_PREPOSITION = "by";
const string WORD_DAMAGE_NOUN = "damage";
const string WORD_DEAL_PAST_TENSE = "dealt";
const string WORD_DODGE_PAST_TENSE = "dodged";
const string WORD_FROM_PREPOSITION = "from";
const string WORD_GAIN_PAST_TENSE = "gained";
const string WORD_GOLD_NOUN = "gold";
const string WORD_IS_PAST_TENSE = "was";
const string WORD_KILL_PAST_TENSE = "killed";
const string WORD_LOSE_PAST_TENSE = "lost";
const string WORD_MISS_PAST_TENSE = "missed";
const string WORD_MOVE_PAST_TENSE = "moved";
const string WORD_SEE_PAST_TENSE = "saw";
const string WORD_TAKE_PAST_TENSE = "took";
const string WORD_TO_PREPOSITION = "to";
const string WORD_USE_PAST_TENSE = "used";


// Character names:

const string NAME_DRAGON = "D";
const string NAME_DROW = "R";
const string NAME_DWARF = "W";
const string NAME_ELF = "E";
const string NAME_GOBLIN = "B";
const string NAME_HALFLING = "L";
const string NAME_HUMAN = "H";
const string NAME_MERCHANT = "M";
const string NAME_ORC = "O";
const string NAME_PLAYER = "PC";
const string NAME_SHADE = "S";
const string NAME_TROLL = "T";
const string NAME_VAMPIRE = "V";


// Display char:

const char CHAR_VERTICAL_WALL = '|';
const char CHAR_HORIZONTAL_WALL = '-';
const char CHAR_FLOOR_TILE = '.';
const char CHAR_DOOR_WAY = '+';
const char CHAR_PASSAGE = '#';

// 92 == '\', compiler won't let me enter the literal
const char CHAR_STAIRS = 92;
const char CHAR_NULL = ' ';

const char CHAR_DRAGON = 'D';
const char CHAR_DROW = 'R';
const char CHAR_DWARF = 'W';
const char CHAR_ELF = 'E';
const char CHAR_GOBLIN = 'B';
const char CHAR_HALFLING = 'L';
const char CHAR_HUMAN = 'H';
const char CHAR_MERCHANT = 'M';
const char CHAR_ORC = 'O';
const char CHAR_PLAYER = '@';
const char CHAR_SHADE = 'S';
const char CHAR_TROLL = 'T';
const char CHAR_VAMPIRE = 'V';

// characters used in reading floor from file only
const char CHAR_READ_POTION_RESTORE_HEALTH = '0';
const char CHAR_READ_POTION_POISON_HEALTH = '1';
const char CHAR_READ_POTION_BOOST_ATTACK = '2';
const char CHAR_READ_POTION_BOOST_DEFENCE = '3';
const char CHAR_READ_POTION_WOUND_ATTACK = '4';
const char CHAR_READ_POTION_WOUND_DEFENCE= '5';
const char CHAR_READ_GOLD_PILE_NORMAL = '6';
const char CHAR_READ_GOLD_PILE_SMALL = '7';
const char CHAR_READ_GOLD_PILE_MERCHANT_HOARD = '8';
const char CHAR_READ_GOLD_PILE_DRAGON_HOARD = '9';


// Direction names:

const string NAME_NORTH = "North";
const string NAME_NORTH_WEST = "North West";
const string NAME_WEST = "West";
const string NAME_SOUTH_WEST = "South West";
const string NAME_SOUTH = "South";
const string NAME_SOUTH_EAST = "South East";
const string NAME_EAST = "East";
const string NAME_NORTH_EAST = "North East";


// GoldPile names (along with article):

const string NAME_GOLD_PILE_SMALL = "a small gold pile";
const string NAME_GOLD_PILE_NORMAL = "a normal gold pile";
const string NAME_GOLD_PILE_MERCHANT_HOARD = "a merchant hoard";
const string NAME_GOLD_PILE_DRAGON_HOARD = "a dragon hoard";


// PotionType names (along with article):

const string NAME_POTION_RESTORE_HEALTH = "a RH";
const string NAME_POTION_POISON_HEALTH = "a PH";
const string NAME_POTION_BOOST_ATTACK = "a BA";
const string NAME_POTION_BOOST_DEFENCE = "a BD";
const string NAME_POTION_WOUND_ATTACK = "a WA";
const string NAME_POTION_WOUND_DEFENCE = "a WD";

const string NAME_POTION_UNKNOWN = "an unknown";


// ItemType names:

const string NAME_ITEM_POTION = "potion";


// Miscellaneous:

const string PERIOD = ".";
