#include <string>
#include <math>
#include <Character.h>
using namespace std;

enum class Race;
enum class Direction;
class Generator;
class Potion;

extern bool merchantsAngered;


void Character::applyPotion(Potion& potion) {
	PotionType type = potion.getType();
	int potency = potion.getPotency();
	
	// health based potions
	if (type == PotionType::RestoreHealth
		|| type == PotionType::PoisonHealth) {
		this->addHP(potency);
	}

	// attack based potions
	if (type == PotionType::BoostAttack
                || type == PotionType::WoundAttack) {
                this->attackbuff += potency;
        }

	// defence based potions
	if (type == PotionType::BoostDefence
                || type == PotionType::WoundDefence) {
                this->defencebuff += potency;
        }

}


void Character::postAttackRoutine(Character& defender) {
	// checks for defender's death
	if (defender.getHP() <= 0) {
		defender.deathRoutine(*this);
	}

}


void Character::addHP(int amount) {
	// when amount added doesn't exceed HPMax
	if (amount <= this->HPMax - this->getHP()) {
		this->HP += amount;
	}

	// when amount added exceeds HPMax
	else {
		this->HP = this->HPMax;
	}

}


void Character::addGold(int amount) {
	this->wallet += amount;
	this->score += amount;
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
	 isPlayer{false}, race{race}, wallet{wallet} {
	int numberOfRaces = 12;

	// an array of character races in order
	Race ordered[numberOfRaces] 
		= {Race::Shade, Race::Drow, Race:: Vampire;, Race::Troll,
		Race::Goblin, Race::Human, Race::Dwarf, Race::Elf
		Race::Orc, Race::Merchant, Race::Dragon, Race::Halfling}

	int index = 0;

	while (ordered[index] != race) {
		++index;
	}

	// all default names in order
	string orderedNames[numberOfRaces] 
		= {"S", "R", "V", "T", "G","H", "W", "E", "O", "M", "D", "L"}

	this->name = orderedNames[index];
}


void Character::attack(Character& defender, Generator& rng) {
	int damage = ceiling((100/(100 + defender.getDefence())) 
		* this->getAttack())

	if (defender.defend(damage, rng)) {}

	else {}

	this->postAttackRoutine(defender);
	
}


bool Character::defend(int incomingDamage, Generator& rng) {
	// if is player, and attacker misses
	if (this->getPlayerState() && !(rng.genHitMiss())) {
		return false;
	}

	this->HP -= incomingDamage;
	return true;
}


void Character::deathRoutine(Character& killer) {
	killer.addGold(this->wallet);
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
