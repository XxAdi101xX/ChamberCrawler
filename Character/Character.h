#include <string>
#include <Subject.h>
#include <Race.h>
enum class Direction;
class Generator;
class Potion;


class Character: public Subject {
private:
	int HPMax;
	int HP;
	int attack;
	int attackBuff;
	int defence;
	int defenceBuff;
	bool isHostile;
	bool isPlayer;
	Race race;
	Cell& currentCell;
	int wallet; // gold that the character owns
	int score; // cumulative gold earnings
	string lastAction; // recorded by various methods

	// helpers:

	// used by move when walking over potion applies
	// the potion on the currentCell to the
	// character, if character is player
	virtual void applyPotion(Potion& potion);

	// used by attack method, checks for death
	// and runs deathRoutine for defender if necessary
	virtual void postAttackRoutine(Character& defender);

	// helper accessors:
	virtual int getAttack(); // returns total attack value
	virtual int getDefence(); // returns total defence value

public:
	// ctor
	Character(Race race);

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

	// accessors:

	virtual int getScore() const; // returns score
	int getHP() const; // returns the current HP
	string getLastAction(); // returns the lastAction done

};


