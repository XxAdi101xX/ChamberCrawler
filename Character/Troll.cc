#include "Troll.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

Troll::Troll(int wallet): Character{TROLL_HP_MAX, TROLL_HP,
	TROLL_ATTACK_VALUE, TROLL_DEFENCE_VALUE, true, Race::Troll, wallet} {}


void Troll::doEndTurnRoutine() {
	this->addHP(TROLL_END_TURN_HEAL);
}
