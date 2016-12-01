#ifndef _GOLDPILE_H_
#define _GOLDPILE_H_

#include "Item.h"

class GoldPile final: public Item {
	// checks if gold is bound by dragon
	bool isBound = true;

 public:
	// constructor
	GoldPile(int value);
	~GoldPile();
	
	// unbinds the gold to allow player to pickup
	void unbind();
	// returns isBound
	bool getBoundState() const;
};

#endif
