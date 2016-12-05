#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <climits>
#include <string>

// Generation info
const int NUMBER_OF_FLOORS = 5;
const int SPAWN_NUMBER_POTION = 10;
const int SPAWN_NUMBER_GOLD_PILE = 10;
const int SPAWN_NUMBER_NPC = 20;
const int DEFAULT_FLOOR_LENGTH = 79;
const int DEFAULT_FLOOR_WIDTH = 25;
const std::string DEFAULT_FLOOR = 
"|-----------------------------------------------------------------------------|\
|                                                                             |\
| |--------------------------|        |-----------------------|               |\
| |..........................|        |.......................|               |\
| |..........................+########+.......................|-------|       |\
| |..........................|   #    |...............................|--|    |\
| |..........................|   #    |..................................|--| |\
| |----------+---------------|   #    |----+----------------|...............| |\
|            #                 #############                |...............| |\
|            #                 #     |-----+------|         |...............| |\
|            #                 #     |............|         |...............| |\
|            ###################     |............|   ######+...............| |\
|            #                 #     |............|   #     |...............| |\
|            #                 #     |-----+------|   #     |--------+------| |\
|  |---------+-----------|     #           #          #              #        |\
|  |.....................|     #           #          #         |----+------| |\
|  |.....................|     ########################         |...........| |\
|  |.....................|     #           #                    |...........| |\
|  |.....................|     #    |------+--------------------|...........| |\
|  |.....................|     #    |.......................................| |\
|  |.....................+##########+.......................................| |\
|  |.....................|          |.......................................| |\
|  |---------------------|          |---------------------------------------| |\
|                                                                             |\
|-----------------------------------------------------------------------------|";


// Enumerations info
const int DIRECTION_ENUMERATION = 8;
const int RACE_ENUMERATION = 12;
const int ITEM_TYPE_ENUMERATION = 2;
const int POTION_TYPE_ENUMERATION = 6;
const int CELL_TYPE_ENUMERATION = 6;


// Item info:
const int POTION_VALUE = 2;
const int POTION_POTENCY_RESTORE_HEALTH = 10;
const int POTION_POTENCY_POISON_HEALTH = -10;
const int POTION_POTENCY_BOOST_ATTACK = 5;
const int POTION_POTENCY_BOOST_DEFENSE = 5;
const int POTION_POTENCY_WOUND_ATTACK = -5;
const int POTION_POTENCY_WOUND_DEFENSE = -5;

const int GOLD_PILE_SMALL_VALUE = 1;
const float GOLD_PILE_SMALL_SPAWN_CHANCE = 2/8;
const int GOLD_PILE_NORMAL_VALUE = 2;
const float GOLD_PILE_NORMAL_SPAWN_CHANCE = 5/8;
const int GOLD_PILE_MERCHANT_HOARD_VALUE = 4;
const int GOLD_PILE_DRAGON_HOARD_VALUE = 6;
const float GOLD_PILE_DRAGON_HOARD_SPAWN_CHANCE = 1/8;


// Race info:
const float SHADE_SPAWN_CHANCE = 1/9;
const int SHADE_HP_MAX = 125;
const int SHADE_HP = 125;
const int SHADE_ATTACK_VALUE =  25;
const int SHADE_DEFENCE_VALUE = 25;
const float SHADE_SCORE_BONUS = 0.5;

const float DROW_SPAWN_CHANCE = 1/9;
const int DROW_HP_MAX = 150;
const int DROW_HP = 150;
const int DROW_ATTACK_VALUE = 25;
const int DROW_DEFENCE_VALUE = 15;
const float DROW_POTION_BONUS = 0.5;

const int VAMPIRE_SPAWN_CHANCE = 1/9;
const int VAMPIRE_HP_MAX = INT_MAX;
const int VAMPIRE_HP = 50;
const int VAMPIRE_ATTACK_VALUE = 25;
const int VAMPIRE_DEFENCE_VALUE = 25;
const int VAMPIRE_ON_HIT_HEAL = 5;

const float TROLL_SPAWN_CHANCE = 1/9;
const int TROLL_HP_MAX = 120;
const int TROLL_HP = 120;
const int TROLL_ATTACK_VALUE = 25;
const int TROLL_DEFENCE_VALUE = 15;
const int TROLL_END_TURN_HEAL = 5;

const float GOBLIN_SPAWN_CHANCE = 1/9;
const int GOBLIN_HP_MAX = 110;
const int GOBLIN_HP = 110;
const int GOBLIN_ATTACK_VALUE = 15;
const int GOBLIN_DEFENCE_VALUE = 20;
const int GOBLIN_LOOT_BONUS = 5;

const float HUMAN_SPAWN_CHANCE = 2/9;
const int HUMAN_HP_MAX = 140;
const int HUMAN_HP = 140;
const int HUMAN_ATTACK_VALUE = 20;
const int HUMAN_DEFENCE_VALUE = 20;
const int HUMAN_NUMBER_OF_GOLD_PILES_DROPPED = 2;
const int HUMAN_DROPPED_GOLD_PILE_VALUE = GOLD_PILE_NORMAL_VALUE;

const float DWARF_SPAWN_CHANCE = 3/18;
const int DWARF_HP_MAX = 100;
const int DWARF_HP = 100;
const int DWARF_ATTACK_VALUE = 20;
const int DWARF_DEFENCE_VALUE = 20;

const float ELF_SPAWN_CHANCE = 1/9;
const int ELF_HP_MAX = 140;
const int ELF_HP = 140;
const int ELF_ATTACK_VALUE = 30;
const int ELF_DEFENCE_VALUE = 10;
const int ELF_NUMBER_OF_EXTRA_ATTACKS = 1;

const float ORC_SPAWN_CHANCE = 1/9;
const int ORC_HP_MAX = 180;
const int ORC_HP = 180;
const int ORC_ATTACK_VALUE = 30;
const int ORC_DEFENCE_VALUE = 25;
const float ORC_DAMAGE_BONUS_TO_GOBLINS = 0.5;

const float MERCHANT_SPWAN_CHANCE = 1/9;
const int MERCHANT_HP_MAX = 30;
const int MERCHANT_HP = 30;
const int MERCHANT_ATTACK_VALUE = 70;
const int MERCHANT_DEFENCE_VALUE = 5;
const int MERCHANT_NUMBER_OF_GOLD_PILES_DROPPED = 1;
const int MERCHANT_DROPPED_GOLD_PILE_VALUE = GOLD_PILE_MERCHANT_HOARD_VALUE;

const int DRAGON_HP_MAX = 150;
const int DRAGON_HP = 150;
const int DRAGON_ATTACK_VALUE = 20;
const int DRAGON_DEFENCE_VALUE = 20;

const float HALFLING_SPAWN_CHANCE = 5/18;
const int HALFLING_HP_MAX = 100;
const int HALFLING_HP = 100;
const int HALFLING_ATTACK_VALUE = 15;
const int HALFLING_DEFENCE_VALUE = 20;
// const float HALFLING_DODGE_CHANCE = 0.5; // chance for attack to miss halfling
#endif
