#ifndef _ITEM_H_
#define _ITEM_H_

#include "ItemType.h"
#include "Defines.cc"
class Item {
	ItemType itemType;
	int value = 0;
 public:
	Item(ItemType itemType, int value);
	virtual ~Item();
	virtual void addGold(int amount) = 0;
	ItemType getItemType();
	int getValue() const;
}

#endif
