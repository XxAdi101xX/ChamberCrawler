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
	{Race::Shade, SHADE_NAME}, 
	{Race::Drow, DROW_NAME}, 
	{Race::Vampire, VAMPIRE_NAME}, 
	{Race::Troll, TROLL_NAME}, 
	{Race::Goblin, GOBLIN_NAME}, 
	{Race::Human, HUMAN_NAME}, 
	{Race::Dwarf, DWARF_NAME}, 
	{Race::Elf, ELF_NAME}, 
	{Race::Orc, ORC_NAME}, 
	{Race::Merchant, MERCHANT_NAME}, 
	{Race::Dragon, DRAGON_NAME}, 
	{Race::Halfling, HALFLING_NAME} 
};


// Direction to direction name mapping
map<Direction, string> directions = {
	{Direction::North, NORTH_NAME}, 
	{Direction::NorthWest, NORTH_WEST_NAME}, 
	{Direction::West, WEST_NAME}, 
	{Direction::SouthWest, SOUTH_WEST_NAME}, 
	{Direction::South,  SOUTH_NAME}, 
	{Direction::SouthEast, SOUTH_EAST_NAME}, 
	{Direction::East, EAST_NAME}, 
	{Direction::NorthEast, NORTH_EAST_NAME} 
};


// GoldPile value to gold pile name mapping
map<int, string> goldPiles = {
	{GOLD_PILE_SMALL_VALUE, GOLD_PILE_SMALL_NAME}, 
	{GOLD_PILE_NORMAL_VALUE, GOLD_PILE_NORMAL_NAME}, 
	{GOLD_PILE_MERCHANT_HOARD_VALUE, GOLD_PILE_MERCHANT_HOARD_NAME}, 
	{GOLD_PILE_DRAGON_HOARD_VALUE, GOLD_PILE_DRAGON_HOARD_NAME} 
};


// PotionType to potion type name mapping
map<PotionType, string> potionTypes = {
	{PotionType::RestoreHealth, POTION_RESTORE_HEALTH_NAME}, 
	{PotionType::PoisonHealth, POTION_POISON_HEALTH_NAME}, 
	{PotionType::BoostAttack, POTION_BOOST_ATTACK_NAME}, 
	{PotionType::BoostDefence, POTION_BOOST_DEFENCE_NAME}, 
	{PotionType::WoundAttack, POTION_WOUND_ATTACK_NAME}, 
	{PotionType::WoundDefence, POTION_WOUND_DEFENCE_NAME} 
};


string makeMsg(string subject, string action, string object) {
	return subject + " " + action + " " + object + " ";
}


string raceToText(Race race) {
	return races[race];
}


string directionToText(Direction direction) {
	return directions[direction];
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
		return potionTypes[type] + " " + ITEM_POTION_NAME;
	}

	return POTION_UNKNOWN_NAME + " " + ITEM_POTION_NAME;
}


