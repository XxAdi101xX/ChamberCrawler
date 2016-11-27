#include <string>
#include <cmath>
#include <vector>
#include "Character.h"
#include "Messaging.h"
//#include "Potion.h"
//#include "Generator.h"
#include "PotionType.h"
#include "Direction.h"
#include "ItemType.h"
#include "CellType.h"
using namespace std;

extern bool merchantsAngered;
extern vector<PotionType> usedPotions;


void Character::applyItem(shared_ptr<Item> item) {
	// gets the item type
	ItemType itemType = item->getItemType();

        // if item is GoldPile
        if (itemType == ItemType::GoldPile) {
                // if GoldPile is not bound
                if (!(item->getBoundState) {
                        this->addGold(item->getValue());
                }

        }

        // if item is Potion
        else if (itemType == ItemType::Potion) {
                this->applyPotion(item);
        }

}


void Character::applyPotion(shared_ptr<Item> potion) {
	PotionType type = potion->getType();
	int potency = potion->getPotency();
	
	// health based potions
	if (type == PotionType::RestoreHealth
		|| type == PotionType::PoisonHealth) {
		this->addHPViaPotion(potency);
	}

	// attack based potions
	else if (type == PotionType::BoostAttack
                || type == PotionType::WoundAttack) {
                this->attackBuff += potency;
        }

	// defence based potions
	else if (type == PotionType::BoostDefence
                || type == PotionType::WoundDefence) {
                this->defenceBuff += potency;
        }

	usedPotions.emplace_back(type);

	// reports what potion was used
	this->addAction(makeMsg(this->name, "used", potionToText(potion)));
}


void Character::postAttackRoutine(Character& defender) {/* nothing by default */}


void Character::addHP(int amount) {
	int HPToBeAdded = amount;
	// if amount added exceeds HPMax
	if (amount > this->HPMax - this->getHP()) {
		HPToBeAdded = this->HPMax - this->getHP();

	}

	// adds HP
	this->HP += HPToBeAdded;

	// reports how much HP was gained
	this->addAction(
		makeMsg(this->name, "gained", to_string(HPToBeAdded) + " HP"));

}


void Character::addHPViaPotion(int amount) {
	this->addHP(amount);
}


void Character::addGold(int amount) {
	this->wallet += amount;
	this->score += amount;

	this->addAction(
		makeMsg(this->name, "gained", to_string(amount) + " gold"));
}


int Character::getTotalAttack() {
	return this->attackValue + this->attackBuff;
}


int Character::getTotalDefence() {
	return this->defenceValue + this->defenceBuff;
}


void Character::setHPMax(int value) {
	this->HPMax = value;
}


void Character::setHP(int value) {
	this->HP = value;
}


void Character::setAttackValue(int value) {
	this->attackValue = value;
}


int getAttack() {
	return this->attackValue;
}


void Character::setDefenceValue(int value) {
	this->defenceValue = value;
}


int getDefence() {
        return this->defenceValue;
}


void Character::setHostile(bool value) {
	this->isHostile = value;
}


int Character::getAttackBuff() {
        return this->attackBuff;
}


int Character::getDefenceBuff() {
        return this->defenceBuff;
}


Character::Character(Race race, int wallet): 
	isHostile{race != Race::Dragon 
	|| (race == Race::Merchant && merchantsAngered) ? true : false},
	 isPlayer{false}, race{race}, wallet{wallet}, name{raceToText(race)} {}


void Character::attack(Character& defender, Generator& rng) {
	int damage = ceil((100/(100 + defender.getTotalDefence())) 
		* this->getTotalAttack());

	if (defender.defend(damage, rng)) {
		// reports hit
		this->addAction(makeMsg(this->name, 
			"dealt " + to_string(damage) + " damage to", 
			defender.getName()));
	}

	else {
		// reports miss
		this->lastAction += 
			makeMsg(this->name, "misses", defender.getName());
	}

	this->postAttackRoutine()

        // checks for defender's death
        if (defender.getHP() <= 0) {
		this->addGold(defender->getWallet());
                defender.deathRoutine(*this);

                this->addAction(makeMsg(this->name, "killed", defender.getName()));
		defender.addAction(
			makeMsg(defender.getName(), 
			"was killed by", this->name));
        }

}


bool Character::defend(int incomingDamage, Generator& rng) {
	// if is player, and attacker misses
	if (this->getPlayerState() && !(rng.genHitMiss())) {
		// reports dodge
		this->addAction(makeMsg(this->name, "dodges", "attack " 
			+ " (" + to_string(incomingDamage) + " damage)"));

		return false;
	}

	this->HP -= incomingDamage;

	// reports damage taken
	this->addAction(makeMsg(this->name, "took", 
		to_string(incomingDamage) + " damage")); 

	return true;
}


void Character::startTurnRoutine() {/* nothing by default */}


void Character::deathRoutine() {/* nothing by default */}


void Character::endTurnRoutine() {/* nothing by default */}


void Character::setPlayer() {
	this->isPlayer = true;
	this->name = "PC";
}
	

void Character::clearBuffs() {
	this->attackBuff = 0;
	this->defenceBuff = 0;
}
	

void Character::move(Direction direction) {
	Cell* cell = (this->currentCell)->getNeighbour(direction);
	if (cell != nullptr) {
		// type of cell attempting to move to
		CellType cellType = cell->getType()

		// seperating cases of non movement for clarity

		// nobody can enter a Wall or Null
		if ((cellType == CellType::Wall) 
			|| (cellType == CellType::Null)) {
			return;
		}

		// NPCs cannot leave their chamber
		if (!(this->isPlayer) && (cellType != CellType::FloorTile)
			&& (cellType != CellType::Stairs)); {
			return;
		}

		// NPCs cannot occupy a tile if it has an item
		if (!(this->isPlayer) && cell->getItem()) {
			return;
		}

		// two characters cannot be on the same cell
		if (cell->getOccupant) {
			return;
		}

		// removes character from currentCell
		(this->currentCell)->setOccupant(this);
		
		// changes currentCell to the new one
		// setOccupant is done in setCell
		this->setCell(cell);
		
		// reports movement
		this->addAction(makeMsg(this->name, "moves", 
			directionToText(direction)));

		// gets the neighbourhood
		vector<Cell*> neighbourhood 
			= (this->currentCell)->getNeighbours();

		// reports all item sightings
		for (auto neighbour: neighbourhood) {
			shared_ptr<Item> item = neighbour.getItem();
			if (item != nullptr) {
				this->addAction(
					makeMsg(this->name, "sees",
					itemToText(item)));
			}

		}

	}

	// if is player, and there's an item on the new cell;
	if (this->isPlayer && currentCell->getItem()) {
		// uses the item
		this->applyItem(currentCell->getItem());

		// remove the item from the cell
		currentCell->setItem(nullptr);
	}

}


void Character::setCell(Cell* cell) {
	this->currentCell = cell;

	(this->currentCell)->setOccupant(this);

}


void Character::addAction(std::string action) {
	this->lastAction += action;
}


int Character::getWallet() {
	return this->wallet;
}


int Character::getScore() const {
	return this->score;
}


int Character::getHP() const {
	return this->HP;
}


bool Character::getPlayerState() const {
	return this->isPlayer;
}


Cell* Character::getCurrentCell() {
	return this->currentCell;
}


string Character::getLastAction() {
	return this->lastAction;
}


string Character::getName() {
	return this->name;
}
