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
	virtual void applyPotion(std::shared_ptr<Item> potion);

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
	void addGold(int amount); // adds gold and thus score as well
	
	// responsible to movement, and calls applyItem
        // if moved over item
	virtual void doMove(Direction direction);

	// helper accessors:

	int getTotalAttack(); // returns total attack value
	int getTotalDefence(); // returns total defence value

	// returns the bonus to attackBuff, default 0
	virtual int getAttackBuffBonus();
	
	// returns the bonus to defenceBuff, default 0
	virtual int getDefenceBuffBonus();
	
	// returns the bonus to score, default 0
	virtual int getScoreBonus();

protected:
	// helper mutators:

	void setHostile(bool value = true); // sets isHostile to value
	void addHP(int amount); // adds HP but does not exceed HPMax       
 
	// helper accessors:

	int getAttackBuffProt(); // returns attackBuff value for subclasses
        int getDefenceBuffProt(); // returns defenceBuff value for subclasses
	int getScoreProt(); // returns score for subclasses


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

	// appends a string action to lastAction
	void addAction(std::string action);

	// accessors:

	int getWallet(); // returns wallet
	int getScore() const; // wrapper for doGetScore, uses NVI idiom
	int getHP() const; // returns the current HP
	bool getPlayerState() const; // returns isPlayer
	bool getHostileState() const; // returns isHostile
	Cell* getCurrentCell(); // returns the currentCell
	std::string getLastAction(); // returns the lastAction done
	std::string getName(); // returns the name of the character

};


#endif


