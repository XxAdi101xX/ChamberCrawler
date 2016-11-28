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

	// used when walking over any item, applies item
	// to character if character is player
	// may call applyPotion
	void applyItem(std::shared_ptr<Item> item);

	// used when walking over potion, applies potion
	// to character if character is player
	virtual void applyPotion(std::shared_ptr<Item> potion);

	// runs after attack
	// normally does nothing, but overrides implements specific
        // racial traits
	virtual void postAttackRoutine(Character& defender);

	// helper mutators:
	
	// adds hp using addHP, wrapper to be overriden
	virtual void addHPViaPotion(int amount);
	void addGold(int amount); // adds gold and thus score as well

	// helper accessors:
	virtual int getTotalAttack(); // returns total attack value
	virtual int getTotalDefence(); // returns total defence value

protected:
	// helper mutators:
	void setHPMax(int value); // sets HPMax to value
	void setHP(int value); // sets HP to value
	void setAttackValue(int value); // sets attackValue to value
	void setDefenceValue(int value); // sets defenceValue to value
	void setHostile(bool value = true); // sets IsHostile to value
	void addHP(int amount); // adds HP but does not exceed HPMax       
 
	// helper accessors:
	int getAttackValue(); // returns attackValue
	int getDefenceValue(); // returns defenceValue
	int getAttackBuff(); // returns attackBuff value
        int getDefenceBuff(); // returns defenceBuff value


public:
	// ctor
	Character(int HPMax int HP, int attackValue int defenceValue, 
		bool isHostile, Race race, int wallet);

	// attack encompasses different parts of a charcter's attack
	// utilizing postAttackRoutine
	// may decide hit or miss in future expansion using rng
	virtual void attack(Character& defender, Generator& rng);

	// defends from incoming damage, evasion is
        // decided here by rng
        virtual bool defend(int incomingDamage, Generator& rng);
        
	// runs at turn start
	// normally does nothing, but overrides implements specific
        // racial traits
	virtual void startTurnRoutine();

	// run upon character death (HP == 0)
        // normally does nothing, but overrides implements specific
        // racial traits
	virtual void deathRoutine();

	// runs at turn end
	// normally does nothing, but overrides implements specific
	// racial traits
	virtual void endTurnRoutine();

	// mutators :

	void setPlayer(); // sets isPlayer to true
	
	void clearBuffs(); // sets buffs to 0, used when entering new floor

	// responsible to movement, and picking up/utilizing
	// items if moved over
	virtual void move(Direction direction);

	// used during initialization to set the character's location
	void setCell(Cell* cell);

	// appends a string action to lastAction
	void addAction(std::string action);

	// accessors:

	int getWallet(); // returns wallet
	virtual int getScore() const; // returns score
	int getHP() const; // returns the current HP
	bool getPlayerState() const; // returns isPlayer
	Cell* getCurrentCell(); // returns the currentCell
	std::string getLastAction(); // returns the lastAction done
	std::string getName(); // returns the name of the character

};


#endif

