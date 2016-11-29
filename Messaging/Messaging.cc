#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Race.h"
#include "Direction.h"
#include "ItemType.h"
#include "PotionType.h"
//#include "Item.h"
//#include "Potion.h"
//#include "GoldPile.h"
#include "Localisation.cc"
#include "Defines.cc"
using namespace std;

// all string literals reside in Localisation.cc
// all value literals reside in Defines.cc

extern vector<PotionType> usedPotions;

// Race to race name mapping
map<Race, string> races = {
	{Race::Shade, NAME_SHADE}, 
	{Race::Drow, NAME_DROW}, 
	{Race::Vampire, NAME_VAMPIRE}, 
	{Race::Troll, NAME_TROLL}, 
	{Race::Goblin, NAME_GOBLIN}, 
	{Race::Human, NAME_HUMAN}, 
	{Race::Dwarf, NAME_DWARF}, 
	{Race::Elf, NAME_ELF}, 
	{Race::Orc, NAME_ORC}, 
	{Race::Merchant, NAME_MERCHANT}, 
	{Race::Dragon, NAME_DRAGON}, 
	{Race::Halfling, NAME_HALFLING} 
};


// Direction to direction name mapping
map<Direction, string> directions = {
	{Direction::North, NAME_NORTH}, 
	{Direction::NorthWest, NAME_NORTH_WEST}, 
	{Direction::West, NAME_WEST}, 
	{Direction::SouthWest, NAME_SOUTH_WEST}, 
	{Direction::South, NAME_SOUTH}, 
	{Direction::SouthEast, NAME_SOUTH_EAST}, 
	{Direction::East, NAME_EAST}, 
	{Direction::NorthEast, NAME_NORTH_EAST} 
};


// GoldPile value to gold pile name mapping
map<int, string> goldPiles = {
	{GOLD_PILE_SMALL_VALUE, NAME_GOLD_PILE_SMALL}, 
	{GOLD_PILE_NORMAL_VALUE, NAME_GOLD_PILE_NORMAL}, 
	{GOLD_PILE_MERCHANT_HOARD_VALUE, NAME_GOLD_PILE_MERCHANT_HOARD}, 
	{GOLD_PILE_DRAGON_HOARD_VALUE, NAME_GOLD_PILE_DRAGON_HOARD} 
};


// PotionType to potion type name mapping
map<PotionType, string> potionTypes = {
	{PotionType::RestoreHealth, NAME_POTION_RESTORE_HEALTH}, 
	{PotionType::PoisonHealth, NAME_POTION_POISON_HEALTH}, 
	{PotionType::BoostAttack, NAME_POTION_BOOST_ATTACK}, 
	{PotionType::BoostDefence, NAME_POTION_BOOST_DEFENCE}, 
	{PotionType::WoundAttack, NAME_POTION_WOUND_ATTACK}, 
	{PotionType::WoundDefence, NAME_POTION_WOUND_DEFENCE} 
};


string makeMsg(string subject, string action, string object) {
	return subject + " " + action + " " + object + PERIOD + " ";
}


string raceToText(Race race) {
	return races[race];
}


string directionToText(Direction direction) {
	return directions[direction];
}


string goldPileToText(const GoldPile goldPile) {
	return goldPiles[goldPile.getValue()];
}


string potionToText(const Potion potion) {
	PotionType type = potion.getPotionType;
	bool used = false;
	
	// check if player has used potion
	for (auto usedPotion: usedPotions) {
		if (usedPotion == type) {
			used = true;
			break;
		}
	}

	if (used) {
		return potionTypes[type] + " " + NAME_ITEM_POTION;
	}

	return NAME_POTION_UNKNOWN + " " + NAME_ITEM_POTION;

}


string itemToText(const shared_ptr<Item> item) {
    if (item == nullptr) {
        return "";
    }

    else if (item->getType() == ItemType::GoldPile) {
        return goldPileToText(*item);
    }

    else if (item->getType() == ItemType::Potion) {
        return potionToText(*item);
    }

}



