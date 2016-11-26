#ifndef _HALFLING_H_
#define _HALFLING_H_

#include <Subject.h>
class Generator;


class Character: public Subject {
public:
	// override defend to add 50% chance to miss
        bool defend(int incomingDamage, Generator& rng) override;
	virtual void setStats() override; // sets Halfling stats
};


#endif


