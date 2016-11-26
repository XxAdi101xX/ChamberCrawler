#ifndef _MESSAGING_H_
#define _MESSAGING_H_

#include <string>
#include <memory>

class Race;
class Direction;

class Item;
class Potion;
class GoldPile;

// creates a message given a subject doing the action, an action
// and the object the action is done on
std::string makeMsg(std::string subject, 
	std::string action, std::string object);


// converts Race enumeration to text
std::string raceToText(Race race);



// converts Direction enumeration to text
std::string directionToText(Direction direction)


// converts Item to text, along with addition info
// from the item it self
std::string itemToText(const std::shared_ptr<Item> item);


// converts GoldPile to text depending on value
std::string goldPileToText(const GoldPile goldPile);


// converts Potion to text, name revealed if potion had been used
potionToText(const Potion potion);


#endif


