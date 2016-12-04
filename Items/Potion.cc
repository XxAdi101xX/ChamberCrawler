#include "Potion.h"
#include "../Defines/Defines.h"
using namespace std;

Potion::Potion(PotionType potionType):Item{ItemType::Potion, POTION_VALUE},
									  potionType{potionType},
									  potency{potionTypeToPotency(potionType)}
									  {}

int Potion::potionTypeToPotency(PotionType potionType) {
	// Different potion potencies layed out in if statements so they can
	// easily be changed/added if required

	int p;
	if (potionType == PotionType::RestoreHealth) {
		return POTION_POTENCY_RESTORE_HEALTH;
	}
	else if (potionType == PotionType::PoisonHealth) {
    	return POTION_POTENCY_POISON_HEALTH;
  	}
	else if (potionType == PotionType::BoostAttack) {
    	return POTION_POTENCY_BOOST_ATTACK;
  	}
	else if (potionType == PotionType::BoostDefence) {
    	return POTION_POTENCY_BOOST_DEFENSE;
  	}
	else if (potionType == PotionType::WoundAttack) {
    	return POTION_POTENCY_WOUND_ATTACK;
  	}
	else if (potionType == PotionType::WoundDefence) {
    	return POTION_POTENCY_WOUND_DEFENSE;
  	}
	return 0;
}

// Destructor
Potion::~Potion() {}

// Return type of potion that affects the player's stats
PotionType Potion::getPotionType() const {
	return potionType;
}

// Potency of the Potion
int Potion::getPotency() const {
	return potency;
}
