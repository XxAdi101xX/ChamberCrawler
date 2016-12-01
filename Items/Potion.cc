#include "Potion.h"
#include "../Defines/Defines.cc"
using namespace std;

Potion::Potion(PotionType potionType):Item{ItemType::Potion, POTION_VALUE}, 
																			potionType{potionType} {
	// Different potion potencies layed out in if statements so they can 
	// easily be changed/added if required
	if (potionType == PotionType::RestoreHealth) {
		potency = POTION_POTENCY_RESTORE_HEALTH;
	}
	else if (potionType == PotionType::PoisonHealth) {
    potency = POTION_POTENCY_POISON_HEALTH;
  }
	else if (potionType == PotionType::BoostAttack) {
    potency = POTION_POTENCY_BOOST_ATTACK;
  }
	else if (potionType == PotionType::BoostDefense) {
    potency = POTION_POTENCY_BOOST_DEFENSE;
  }
	else if (potionType == PotionType::WoundAttack) {
    potency = POTION_POTENCY_WOUND_ATTACK;
  }
	else if (potionType == PotionType::WoundDefense) {
    potency = POTION_POTENCY_WOUND_DEFENSE;
  }
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
