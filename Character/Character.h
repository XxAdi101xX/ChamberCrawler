#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include <memory>
//#include <Subject.h>
#include "Race.h"

enum class Direction;
class Item;
class Generator;
class Potion;
class Cell;

class Character/*: public Subject*/ {
private:
	int HPMax;
	int HP;
	int attackValue;
	int attackBuff;
	int defenceValue;
	int defenceBuff;
	bool isHostile;
	bool isPlayer;
	Race race;
	Cell* currentCell;
	int wallet; // gold that the character owns
	int score; // cumulative gold earnings
	std::string lastAction; // recorded by various methods
	std::string name;

	// helpers:

	// used by move when walking over potion applies
	// the potion on the currentCell to the
	// character, if character is player
	virtual void applyPotion(std::shared_ptr<Item> potion);

	// used by attack method, checks for death
	// and runs deathRoutine for defender if necessary
	virtual void postAttackRoutine(Character& defender);

	// helper mutators:
	void addHP(int amount); // adds HP but does not exceed HPMax
	void addGold(int amount); // adds gold and thus score as well

	// helper accessors:
	virtual int getAttack(); // returns total attack value
	virtual int getDefence(); // returns total defence value

public:
	// ctor
	Character(Race race, int wallet);

	// attack encompasses different parts of a charcter's attack
	// utilizing postAttackRoutine
	// may decide hit or miss in future expansion using rng
	virtual void attack(Character& defender, Generator& rng);

	// defends from incoming damage, evasion is
        // decided here by rng
        virtual bool defend(int incomingDamage, Generator& rng);

	// run upon character death (HP == 0)
        // called by postAttackRoutine
        // gives killer gold
        virtual void deathRoutine(Character& killer);

	// normally does nothing, but overrides implements specific
	// racial traits
	virtual void endTurnRoutine();

	// mutators :

	void setPlayer(); // sets isPlayer to true
	
	// uses template method pattern
	// to set stats of all different races
	virtual void setStats() = 0;
	void clearBuffs(); // sets buffs to 0, used when entering new floor

	// responsible to movement, and picking up/utilizing
	// items if moved over
	void move(Direction direction);

	// used during initialization to set the character's location
	void setCell(Cell* cell);

	// accessors:

	virtual int getScore() const; // returns score
	int getHP() const; // returns the current HP
	bool getPlayerState() const; // returns isPlayer
	Cell* getCurrentCell(); // returns the currentCell
	std::string getLastAction(); // returns the lastAction done
	std::string getName(); // returns the name of the character

};


#endif


