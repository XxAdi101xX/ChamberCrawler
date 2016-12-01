#ifndef _ITEM_H_
#define _ITEM_H_

#include "ItemType.h"

class Item {
	ItemType itemType;
	int value = 0;
 public:
	Item(ItemType itemType, int value);
	virtual ~Item();
	ItemType getItemType();
	int getValue() const;
};

#endif
