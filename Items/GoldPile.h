#ifndef _GOLDPILE_H_
#define _GOLDPILE_H_

#include "Item.h"
class GoldPile final: public Item {
	bool isBound = true;
 public:
	GoldPile(int value);
	~GoldPile();
	void unbind();
	bool getBoundState() const;
}

#endif
