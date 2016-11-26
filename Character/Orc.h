#ifndef _ORC_H_
#define _ORC_H_

#include <Character.h>
class Generator;


class Orc final: public Character {
public:
	// overrides attack to deal double damage to Goblin
	virtual void attack(Character& defender, Generator& rng) override;
	virtual void setStats() override; // sets Orc stats

};


#endif


