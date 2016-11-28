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
                if (!(item->getBoundState)) {
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


void Character::doStartTurnRoutine() {/* nothing by default */}


void Character::postAttackRoutine(Character& defender, bool hit, Generator& rng) {
	// nothing by default 
}


void Character::deathRoutine() {/* nothing by default */}


void Character::doEndTurnRoutine() {/* nothing by default */}


bool Character::defend(Character& attacker, 
		int& incomingDamage, Generator& rng) {
	// modifies damage and hit chance if necessary
	if(this->takeDamageFrom(attacker, incomingDamage, rng)) {
		// if is attack hits or is not player
        	if (rng.genHitMiss() || !(this->getPlayerState())) {
			// deduct HP
        		this->HP -= incomingDamage;

                	// reports damage taken
               		this->addAction(makeMsg(this->name, "took",
                	        to_string(incomingDamage) + " damage"));

        	        return true;
	
		}

	}

        // reports dodge
        this->addAction(makeMsg(this->name, "dodges", "attack ("
               + to_string(incomingDamage) + " damage)"));
	return false;
}


bool Character::dealDamageTo(Character& defender, int& damage, 
	Generator& rng) {
	// no changes by default
	return true;
}


bool Character::takeDamageFrom(Character& attacker, int& damage, 
	Generator& rng) {
	// no changes by default
	return true;
}


void Character::addHPViaPotion(int amount) {
        this->addHP(amount);
}


void Character::doMove(Direction direction) {
        Cell* cell = (this->currentCell)->getNeighbour(direction);
        if (cell != nullptr) {
                // type of cell attempting to move to
                CellType cellType = cell->getCellType();

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

                // otherwise move as normal

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
                        shared_ptr<Item> item = neighbour->getItem();
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


int Character::getTotalAttack() {
	return this->attackValue + this->attackBuff 
		+ this->getAttackBuffBonus();
}


int Character::getTotalDefence() {
	return this->defenceValue + this->defenceBuff 
		+ this->getDefenceBuffBonus();
}


int Character::getAttackBuffBonus() {
	// 0 by default
	return 0;
}


int Character::getDefenceBuffBonus() {
	// 0 by default
        return 0;
}


int Character::getScoreBonus() {
	// 0 by default
	return 0;
}


void Character::setHostile(bool value) {
	this->isHostile = value;
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
        this->addAction(
                makeMsg(this->name, "gained", to_string(HPToBeAdded) + " HP"));

}


void Character::addGold(int amount) {
        this->wallet += amount;
        this->score += amount;

        this->addAction(
                makeMsg(this->name, "gained", to_string(amount) + " gold"));
}


int Character::getAttackBuffProt() {
        return this->attackBuff;
}


int Character::getDefenceBuffProt() {
        return this->defenceBuff;
}


int Character::getScoreProt() {
	return this->score;
}


Character::Character(int HPMax, int HP, int attackValue, int defenceValue,
                bool isHostile, Race race, int wallet): 
	HPMax{HPMax}, HP{HP}, attackValue{attackValue}, 
	defenceValue{defenceValue}, isHostile{isHostile}, isPlayer{false}, 
	race{race}, wallet{wallet}, name{raceToText(race)} {}


void Character::attack(Character& defender, Generator& rng) {
	int damage = ceil((100/(100 + defender.getTotalDefence())) 
		* this->getTotalAttack());
	
	bool firstRollForHit = this->dealDamageTo(defender, damage, rng);

	if (firstRollForHit) {
		if (defender.defend(*this, damage, rng)) {
			// reports hit
			this->addAction(makeMsg(this->name, 
				"dealt " + to_string(damage) + " damage to", 
				defender.getName()));
		}

	}

	else {
		// reports miss
                this->lastAction +=
                        makeMsg(this->name, "misses", defender.getName());	
	}

	this->postAttackRoutine(defender, firstRollForHit, rng);

        // checks for defender's death
        if (defender.getHP() <= 0) {
		this->addGold(defender.getWallet());
                defender.deathRoutine();

                this->addAction(makeMsg(this->name, "killed", defender.getName()));
		defender.addAction(
			makeMsg(defender.getName(), 
			"was killed by", this->name));
        }

}


void Character::startTurnRoutine() {
	this->doStartTurnRoutine();
}


void Character::endTurnRoutine() {
	this->doEndTurnRoutine();
}


void Character::setPlayer() {
	this->isPlayer = true;
	this->isHostile = false;
	this->name = "PC";
}
	

void Character::clearBuffs() {
	this->attackBuff = 0;
	this->defenceBuff = 0;
}
	

void Character::move(Direction direction) {
	doMove(direction);
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


Race Character::getRace() const {
	return this->race;
}


bool Character::getPlayerState() const {
	return this->isPlayer;
}


bool Character::getHostileState() const {
	return this->isHostile;
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


char getInfo() {
	if (this->isPlayer) {
		return '@';
	}

	return this->name;
}


