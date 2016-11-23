#include <string>
#include <Character.h>
using namespace std;

enum class Race;
enum class Direction;
class Generator;
class Potion;


void Character::applyPotion(Potion& potion) {}


void Character::postAttackRoutine(Character& defender) {}


int Character::getAttack() {}


int Character::getDefence() {}
	

Character::Character(Race race, int wallet) {}


void Character::attack(Character& defender, Generator& rng) {}


bool Character::defend(int incomingDamage, Generator& rng) {}


void Character::deathRoutine(Character& killer) {}


void Character::endTurnRoutine() {}


void Character::setPlayer() {}
	

void Character::clearBuffs() {}
	

void Character::move(Direction direction) {}


void Character::setCell(Cell& cell) {}


int Character::getScore() const {}


int Character::getHP() const {}


string Character::getLastAction() {}


