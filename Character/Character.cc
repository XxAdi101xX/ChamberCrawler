#include <string>
#include <cmath>
#include <vector>
#include "Character.h"
#include "../Items/Potion.h"
#include "../Items/GoldPile.h"
#include "../Cell/Cell.h"
#include "../Generator/Generator.h"
#include "../Enumerations/PotionType.h"
#include "../Enumerations/Direction.h"
#include "../Enumerations/ItemType.h"
#include "../Enumerations/CellType.h"
#include "../Messaging/Messaging.h"
#include "../Info/Info.h"
#include "../Localisation/Localisation.h"
using namespace std;

// note that all string literals for reporting messages are
// stored in Localisation.cc

extern vector<PotionType> usedPotions;


void Character::applyPotion(const shared_ptr<Potion> potion) {
	PotionType type = potion->getPotionType();
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
	this->addAction(makeMsg(this->name, WORD_USE_PAST_TENSE , potionToText(potion)));
}


void Character::doStartTurnRoutine(Generator& rng) {/* nothing by default */}


void Character::postAttackRoutine(Character& defender,
	bool hit, Generator& rng) {
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
		this->addAction(makeMsg(attacker.getName(), WORD_DEAL_PAST_TENSE + " "
		+ to_string(incomingDamage) + " " + WORD_DAMAGE_NOUN + " "
		+ WORD_TO_PREPOSITION, this->name));

		return true;
		}

	}

	// reports dodge
	this->addAction(makeMsg(this->name, WORD_DODGE_PAST_TENSE + " "
		+ WORD_ATTACK_NOUN + " (" + to_string(incomingDamage) + " "
		+ WORD_DAMAGE_NOUN + ") " + WORD_FROM_PREPOSITION,
		attacker.getName()));

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
	shared_ptr<Cell> cell = (this->currentCell)->getNeighbour(direction);
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
			&& (cellType != CellType::Stairs)) {

			return;
		}

		// nobody can walk over a potion
		if (cell->getItem() && (cell->getItem())->getItemType()
			== ItemType::Potion) {

			return;
		}

		// NPCs cannot occupy a tile if it has an item
		if (!(this->isPlayer) && cell->getItem()) {

			return;
		}

		// two characters cannot be on the same cell
		if (cell->getOccupant()) {
			return;
		}

		// otherwise move as normal

		// removes character from currentCell
		(this->currentCell)->setOccupant(nullptr);

		// changes currentCell to the new one
		// setOccupant is done in setCell
		this->setCell(cell);

		// reports movement
		this->addAction(makeMsg(this->name, WORD_MOVE_PAST_TENSE,
			directionToText(direction)));

		// gets the neighbourhood
		vector<shared_ptr<Cell>> neighbourhood = (this->currentCell)->getNeighbours();

		// reports all item sightings
		for (auto neighbour: neighbourhood) {
			shared_ptr<Item> item = neighbour->getItem();

			if (item != nullptr) {
				this->addAction(makeMsg(this->name, WORD_SEE_PAST_TENSE,
					itemToText(item)));
			}

		}

	}

	// if is player, and there's an item on the new cell (not potion);
	if (this->isPlayer && currentCell->getItem()) {
		// uses the item
		this->applyItem(currentCell->getItem());

		// remove the item from the cell
		currentCell->setItem(nullptr);
	}

}


void Character::addAction(string action) {
	this->lastAction += action;
}


int Character::getTotalAttack() const {
	return this->attackValue
		+ this->attackBuff + this->getAttackBuffBonus();
}


int Character::getTotalDefence() const {
	return this->defenceValue
		+ this->defenceBuff + this->getDefenceBuffBonus();
}


int Character::getAttackBuffBonus() const {
	// 0 by default
	return 0;
}


int Character::getDefenceBuffBonus() const {
	// 0 by default
	return 0;
}


int Character::getScoreBonus() const {
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

	// reports how much HP was gained/lost
	this->addAction(makeMsg(this->name, HPToBeAdded >= 0
		? WORD_GAIN_PAST_TENSE : WORD_LOSE_PAST_TENSE,
		to_string(HPToBeAdded >= 0 ? HPToBeAdded : -1 * HPToBeAdded)
		+ " " + WORD_HP_NOUN));

}


void Character::addGold(int amount) {
	this->wallet += amount;
	this->score += amount;

	this->addAction(makeMsg(this->name, WORD_GAIN_PAST_TENSE, to_string(amount)
		+ " " + WORD_GOLD_NOUN));
}


int Character::getAttackBuffProt() const {
	return this->attackBuff;
}


int Character::getDefenceBuffProt() const {
	return this->defenceBuff;
}


int Character::getScoreProt() const {
	return this->score;
}


Character::Character(int HPMax, int HP, int attackValue, int defenceValue,
	bool isHostile, Race race, int wallet):

	HPMax{HPMax}, HP{HP}, attackValue{attackValue},
	defenceValue{defenceValue}, isHostile{isHostile}, isPlayer{false},
	race{race}, wallet{wallet}, name{raceToText(race)}

	{}


void Character::applyItem(shared_ptr<Item> item) {
    // gets the item type
    ItemType itemType = item->getItemType();

    // if item is GoldPile
    if (itemType == ItemType::GoldPile) {
        // if GoldPile is not bound
        if (!(static_pointer_cast<GoldPile>(item)->getBoundState())) {
                this->addGold(item->getValue());
        }

    }

    // if item is Potion
    else if (itemType == ItemType::Potion) {
        this->applyPotion(static_pointer_cast<Potion>(item));
    }

}


void Character::attack(Character& defender, Generator& rng) {
	int damage = ceil((100/(100 + defender.getTotalDefence()))
		* this->getTotalAttack());

	bool firstRollForHit = this->dealDamageTo(defender, damage, rng);

	if (firstRollForHit) {
		if (defender.defend(*this, damage, rng)) {
			// reports hit
			this->addAction(makeMsg(this->name, WORD_DEAL_PAST_TENSE + " "
				+ to_string(damage) + " " + WORD_DAMAGE_NOUN + " "
				+ WORD_TO_PREPOSITION, defender.getName() + " ("
				+ to_string(defender.getHP()) + ")"));
		}

	}

	else {
		// reports miss
		this->addAction(makeMsg(this->name, WORD_MISS_PAST_TENSE + " ("
		+ to_string(damage) + " " + WORD_DAMAGE_NOUN + ")",
		defender.getName()));
	}

	this->postAttackRoutine(defender, firstRollForHit, rng);

	// checks for defender's death
	if (defender.getHP() <= 0) {
	this->addGold(defender.getWallet());

	defender.deathRoutine();

	this->addAction(
			makeMsg(this->name, WORD_KILL_PAST_TENSE, defender.getName()));

	defender.addAction(makeMsg(defender.getName(), WORD_IS_PAST_TENSE + " "
		+ WORD_KILL_PAST_TENSE + " " + WORD_BY_PREPOSITION, this->name));
	}

}


void Character::startTurnRoutine(Generator& rng) {
	this->doStartTurnRoutine(rng);
}


void Character::endTurnRoutine() {
	this->doEndTurnRoutine();
}


void Character::setPlayer() {
	this->isPlayer = true;
	this->isHostile = false;
	this->wallet = 0;
	this->name = NAME_PLAYER;
}


void Character::clearBuffs() {
	this->attackBuff = 0;
	this->defenceBuff = 0;
}


void Character::move(Direction direction) {
	doMove(direction);
}


void Character::setCell(std::shared_ptr<Cell> cell) {
	this->currentCell = cell;

	if (cell) {
		cell->setOccupant(shared_from_this());
	}

}


void Character::clearLastAction() {
    this->lastAction = "";
}


int Character::getWallet() const {
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


shared_ptr<Cell> Character::getCurrentCell() const {
	return this->currentCell;
}


string Character::getLastAction() const {
	return this->lastAction;
}


string Character::getName() const {
	return this->name;
}


Info Character::getInfo() const {
	Info characterInfo;

	// sets fields with proper info
	characterInfo.race = this->getRace();
	characterInfo.gold = this->wallet;
	characterInfo.HP = this->getHP();
	characterInfo.attackValue = this->getTotalAttack();
	characterInfo.defenceValue = this->getTotalDefence();

	characterInfo.coordinates = (this->currentCell)->getCoords();
	characterInfo.displayChar = this->isPlayer ? CHAR_PLAYER : this->name[1];
	characterInfo.lastAction = this->lastAction;

	return characterInfo;
}
