#include <Character.h>
using namespace std;

class Potion;

class Drow final: public Character {
private:
	// overrides the normal apply potion
	// to amplify effects by 50% rounded up
	// but only for health potions
	// to avoid rounding errors
	virtual void applyPotion(Potion potion) override;
	virtual int getAttack() override; // amplfies potion effects by 50%
	virtual int getDefence() override; // amplifies potion effects by 50%

public:
	virtual void setStats() override; // set stats for a Drow

};
