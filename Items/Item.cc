#include "Item.h"
#include "../Defines/Defines.cc"
using namespace std;

// Constructor
Item::Item(ItemType itemType, int value): itemType{itemType}, value{value} {}

// Destructor
Item::~Item() {}

// Returns type of Item
ItemType Item::getItemType() {
	return itemType;
}

// Returns value
int Item::getValue() const {
	return value;
}
