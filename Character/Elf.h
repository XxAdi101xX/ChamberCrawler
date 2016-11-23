#include <Character.h>
class Generator;


class Elf final: public Character {
public:
	// overrides attack to attack twice except against Drow
	virtual void attack(Character& defender, Generator& rng) override;
	virtual void setStats() override; // sets Elf stats

};

