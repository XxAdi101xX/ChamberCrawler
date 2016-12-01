#include "Item.h"
#include "ItemType.h"
using namespace std;
 
Item::Item(ItemType itemType, int value): itemType{itemType}, value{value} {}

Item::~Item() {}

ItemType Item::getItemType() {
	return itemType;
}

int Item::getValue() const {
	return value;
}
