#include<string>
#include<memory>
using namespace std;

enum class Race;
enum class Direction;
class Item;

extern vector<PotionType> usedPotions;


string makeMsg(string subject, string action, string object) {
	return subject + " " + action + " " + object + " ";
}


string raceToText(Race::race) {
	int numberOfRaces = 12;

        // an array of character races in order
        Race orderedRaces[numberOfRaces]
                = {Race::Shade, Race::Drow, Race:: Vampire;, Race::Troll,
                Race::Goblin, Race::Human, Race::Dwarf, Race::Elf
                Race::Orc, Race::Merchant, Race::Dragon, Race::Halfling};

        int index = 0;

	// traverses orderedRaces to find match
        while (orderedRaces[index] != race) {
                ++index;
        }

        // all default names in order
        string orderedRaceNames[numberOfRaces]
                = {"S", "R", "V", "T", "G","H", "W", "E", "O", "M", "D", "L"};

	// uses matching index
        return orderedRaceNames[index];
}


string directionToText(Direction:: direction) {
	int numberOfDirections = 8;

        // an array of directions in order
        Direction orderedDirections[numberOfDirections]
                = {Direction::North, Direction::NorthWest, 
		Direction::West, Direction::SouthWest, 
		Direction::South, Direction::SouthEast, 
		Direction::East, Direction::NortheEast};

        int index = 0;

	// traverses orderedDirctions to find match
        while (orderedDirection[index] != Direction) {
                ++index;
        }

        // all directions as text in order
        string orderedDirectionNames[numberOfDirections]
                = {"North", "North West", "West", "South West", 
		"South","South East", "East", "North East"};

	// uses matching index
        return orderedDirectionNames[index];
}


string itemToText(const shared_ptr<Item> item) {
	if (item == nullptr) {
		return "";
	}

	else if (item->getType() == GoldPile) {
		return goldPileToText(*item);		
	}

	else if (item->getType() == Potion) {
		return potionToText(*item);
	}

}


string goldPileToText(const GoldPile goldPile) {
	int value = goldPile->getValue();

	int numberOfGoldPiles = 4;

        // an array of GoldPiles in order
        int orderedGoldPiles[numberOfGoldPiles] = {1, 2, 4, 6};

        int index = 0;

        // traverses orderedGoldPiles to find match
        while (orderedGoldPiles[index] != value) {
                ++index;
        }

        // all GoldPiles as text in order
        string orderedGoldPileNames[numberOfGoldPiles]
                = {"a small gold pile", "a normal gold pile", 
		"a merchant hoard", "a dragon hoard"};

        // uses matching index
        return orderedGoldPileNames[index];
}


string potionToText(const Potion potion) {
	PotionType type = potion->getPotionType;
	bool used = false;
	
	// check if player has used potion
	for (auto usedPotion: usedPotions) {
		if (usedPotion == type) {
			seen = true;
			break;
		}
	}

	string output;

	if (used) {
		int numberOfPotionTypes = 6;

        	// an array of PotionTypes in order
        	PotionType orderedPotionTypes[numberOfPotionTypes] 
			= {PotionType::RestoreHealth, 
			PotionType::PoisonHealth, 
			PotionType::BoostAttack, 
			PotionType::BoostDefence, 
			PotionType::WoundAttack, 
			PotionType::WoundDefence};

        	int index = 0;

        	// traverses orderedPotionTypes to find match
        	while (orderedPotionTypes[index] != value) {
               		++index;
        	}

        	// all PotionTypes as text in order
        	string orderedPotionTypeNames[numberOfPotionTypes]
                	= {"a RH", "a PH", "a BA", "a BD", "a WA", "a WD"};

        	// uses matching index
        	output += orderedPotionTypeNames[index];

	}

	else {
		output += "an unknown";
	}

	return output + " potion";
}


