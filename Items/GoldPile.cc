#include "GoldPile.h"
#include "../Defines/Defines.cc"
using namespace std;

GoldPile::GoldPile(int value): Item{ItemType::GoldPile, value} {
	if (value != GOLD_PILE_DRAGON_HOARD_VALUE) {
		unbind();	
	}
}

GoldPile::~GoldPile() {}

// unbinds the gold to allow player to pick it up
void GoldPile::unbind() {
	isBound = false;	
}

// checks if the gold is bound by a dragon
bool GoldPile::getBoundState() const {
	return isBound;
}
