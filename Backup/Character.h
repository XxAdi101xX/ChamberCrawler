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

	// helpers mutators:

	// used when walking over any item, applies item
	// to character if character is player
	// may call applyPotion
	void applyItem(std::shared_ptr<Item> item);

	// used when walking over potion, applies potion
	// to character if character is player
	void applyPotion(std::shared_ptr<Item> potion);

        // runs at turn start
        // normally does nothing, but overrides implements specific
        // racial traits
        virtual void doStartTurnRoutine();

        // runs after attack
        // normally does nothing, but overrides implements specific
        // racial traits
        virtual void postAttackRoutine(Character& defender, 
		bool hit, Generator& rng);

        // run upon character death (HP == 0)
        // normally does nothing, but overrides implements specific
        // racial traits
        virtual void deathRoutine();

        // runs at turn end
        // normally does nothing, but overrides implements specific
        // racial traits
        virtual void doEndTurnRoutine();

	// defends from incoming damage, evasion is
        // decided here by rng
        bool defend(Character& attacker, int& incomingDamage, Generator& rng);

	// the following two functions are made seperate to differentiate
	// one-to-many, and many-to-one relationships when it comes
	// to taking/dealing damage

	// called by attack, modifies the damage value, and hit chance based
	// on race relationship of attacker with respect to the defender
	// returns true for hit, false otherwise
	virtual bool dealDamageTo(Character& defender, 
		int& damage, Generator& rng);

	// called by defend, modifies the damage value, and hit chance based
	// on race relationsip of defender with respect to the attacker
	// returns true for hit, false otherwise
	virtual bool takeDamageFrom(Character& attacker, 
		int& damage, Generator& rng);
	
	// adds hp using addHP, wrapper to be overriden
	virtual void addHPViaPotion(int amount);
	
	// responsible to movement, and calls applyItem
        // if moved over item
	virtual void doMove(Direction direction);

        // appends a string action to lastAction
        void addAction(std::string action);

	// helper accessors:

	int getTotalAttack() const; // returns total attack value
	int getTotalDefence() const; // returns total defence value

	// returns the bonus to attackBuff, default 0
	virtual int getAttackBuffBonus() const;
	
	// returns the bonus to defenceBuff, default 0
	virtual int getDefenceBuffBonus() const;
	
	// returns the bonus to score, default 0
	virtual int getScoreBonus() const;

protected:
	// helper mutators:

	void setHostile(bool value = true); // sets isHostile to value
	void addHP(int amount); // adds HP but does not exceed HPMax
	void addGold(int amount); // adds gold and thus score as well
 
	// helper accessors:

	int getAttackBuffProt() const; // returns attackBuff value for subclasses
        int getDefenceBuffProt() const; // returns defenceBuff value for subclasses
	int getScoreProt() const; // returns score for subclasses


public:
	// ctor
	Character(int HPMax, int HP, int attackValue, int defenceValue, 
		bool isHostile, Race race, int wallet);

	// attack encompasses different parts of a charcter's attack
	// utilizing postAttackRoutine
	// may decide hit or miss in future expansion using rng
	void attack(Character& defender, Generator& rng);
 
	// wrapper for doStartTurnRoutine, uses NVI idiom
	void startTurnRoutine();

	// wrapper for doEndTurnRoutine, uses NVI idiom
	void endTurnRoutine();

	// mutators :

	void setPlayer(); // sets isPlayer to true
	
	void clearBuffs(); // sets buffs to 0, used when entering new floor

	// wrapper for doMove, uses NVI idiom
	void move(Direction direction);

	// used during initialization to set the character's location
	void setCell(Cell* cell);

	// accessors:

	int getWallet() const; // returns wallet
	int getScore() const; // wrapper for doGetScore, uses NVI idiom
	int getHP() const; // returns the current HP
	Race getRace() const; // returns race
	bool getPlayerState() const; // returns isPlayer
	bool getHostileState() const; // returns isHostile
	Cell* getCurrentCell() const; // returns the currentCell
	std::string getLastAction() const; // returns the lastAction done
	std::string getName() const; // returns the name of the character
	char getInfo() const; // returns information for observer

};


#endif


