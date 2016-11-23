#include <Subject.h>
using namespace std;


class Character: public Subject {
public:
	// override defend to add 50% chance to miss
        bool defend(int incomingDamage, Generator rng) override;
	virtual void setStats() override; // sets Halfling stats
};


