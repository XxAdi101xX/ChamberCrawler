#include <Character.h>
using namespace std;


class Orc final: public Character {
public:
	// overrides attack to deal double damage to Goblin
	virtual void attack(Character defender, Generator rng)  override;
	virtual void setStats() override; // sets Orc stats

};


