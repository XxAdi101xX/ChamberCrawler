#ifndef _POTION_H_
#define _POTION_H_

#include "Item.h"
#include "../Enumerations/PotionType.h"

class Potion final: public Item {
	PotionType potionType;
	const int potency;

	int potionTypeToPotency(PotionType potionType);
 public:
	Potion(PotionType potionType);
	~Potion();
	PotionType getPotionType() const;
	int getPotency() const;
};

#endif
