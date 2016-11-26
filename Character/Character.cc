#include <string>
#include <cmath>
#include "Character.h"
#include "Messaging.h"
using namespace std;

enum class Race;
enum class Direction;
class Generator;
class Potion;

extern bool merchantsAngered;
extern vector<PotionType> usedPotions;


void Character::applyPotion(Potion& potion) {
	PotionType type = potion.getType();
	int potency = potion.getPotency();
	
	// health based potions
	if (type == PotionType::RestoreHealth
		|| type == PotionType::PoisonHealth) {
		this->addHP(potency);
	}

	// attack based potions
	else if (type == PotionType::BoostAttack
                || type == PotionType::WoundAttack) {
                this->attackbuff += potency;
        }

	// defence based potions
	else if (type == PotionType::BoostDefence
                || type == PotionType::WoundDefence) {
                this->defencebuff += potency;
        }

	usedPotions.emplace_back(type);

	// reports what potion was used
	this->lastAction += 
		makeMsg(this->name, "used", potionToText(potion));
}


void Character::postAttackRoutine(Character& defender) {
	// checks for defender's death
	if (defender.getHP() <= 0) {
		defender.deathRoutine(*this);

		this->lastAction += 
			makeMsg(this->name, "killed" defender.getName());
	}

}


void Character::addHP(int amount) {
	int HPToBeAdded = amount;
	// if amount added exceeds HPMax
	if (amount > this->HPMax - this->getHP()) {
		HPToBeAdded = this->HPMax - this->getHP();

	}

	// adds HP
	this->HP += HPToBeAdded;

	// reports how much HP was gained
	this->lastAction +=
		makeMsg(this->name, "gained", to_string(HPToBeAdded) + " HP");

}


void Character::addGold(int amount) {
	this->wallet += amount;
	this->score += amount;

	this->lastAction += 
		makeMsg(this->name, "gained", to_string(amount) + " gold");
}


int Character::getAttack() {
	return this->attack + this->attackBuff;
}


int Character::getDefence() {
	return this->defence + this->defenceBuff;
}
	

Character::Character(Race race, Cell currentCell; int wallet): 
	isHostile{race != Race::Dragon 
	|| (race == Merchant && merchantsAngered) ? true : false},
	 isPlayer{false}, race{race}, wallet{wallet}, name{raceToText(race)} {}


void Character::attack(Character& defender, Generator& rng) {
	int damage = ceil((100/(100 + defender.getDefence())) 
		* this->getAttack())

	if (defender.defend(damage, rng)) {
		// reports hit
		this->lastAction += 
			makeMsg(this->name, 
			"dealt " + to_string(damage) + " damage to", 
			defender.getName());
	}

	else {
		// reports miss
		this->lastAction += 
			makeMsg(this->name, "misses", defender.getName());
	}

	this->postAttackRoutine(defender);
	
}


bool Character::defend(int incomingDamage, Generator& rng) {
	// if is player, and attacker misses
	if (this->getPlayerState() && !(rng.genHitMiss())) {
		// reports dodge
		this->lastAction +=
			makeMsg(this->name, "dodges", 
			"attack " + " (" + to_damage(incomingDamage) + 
			" damage)";

		return false;
	}

	this->HP -= incomingDamage;

	// reports damage taken
	this->lastAction +=
		makeMsg(this->name, "took", 
		to_string(incomingDamage) + " damage"); 

	return true;
}


void Character::deathRoutine(Character& killer) {
	// gives money to killer
	killer.addGold(this->wallet);

	// reports death
	this->lastAction +=
		makeMsg(this->name, "was killed by", killer.getName());
}


void Character::endTurnRoutine() {}


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
		this->setCell(cell);
		
		// reports movement
		this->lastAction +=
			makeMsg(this->name, "moves", 
			directionToText(direction));

		for (auto neighbour: 
			this->currentCell->getNeighbours()) {
			shared_ptr<Item> item = neighbour.getItem();
			if (item != nullptr) {
				this->lastAction +=
					makeMsg(this->name, "sees",
						itemToText(item));
			}

		}

	}

	// finds the item on the new cell
	shared_ptr<Item> item = currentCell.getItem();
	ItemType itemType = item->getItemType();

	// if item exists
	if (item != nullptr) {
		// if item is GoldPile
		if (itemType == ItemType::GoldPile) {
			this->addGold(item->getValue());
		}

		// if item is Potion
		else if (itemType == Potion) {
			this->applyPotion(*item);
		}

	}

}


void Character::setCell(Cell* cell) {
	this->currentCell = cell;
}


int Character::getScore() const {
	return this->score;
}


int Character::getHP() const {
	return this->HP;
}


bool Character::getPlayerState const {
	return this->isPlayer;
}


Cell* Character::getCurrentCell {
	return this->currentCell;
}


string Character::getLastAction() {
	return this->lastAction;
}


string Character::getName() {
	return this->name;
}
