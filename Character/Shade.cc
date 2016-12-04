#include "Shade.h"
#include "../Defines/Defines.h"
using namespace std;

// many literal values have been converted to variables,
// and stored in Defines.cc

Shade::Shade(int wallet): Character{SHADE_HP_MAX, SHADE_HP,
	SHADE_ATTACK_VALUE, SHADE_DEFENCE_VALUE, true, Race::Shade, wallet} {}


int Shade::getScoreBonus() const {
	return SHADE_SCORE_BONUS * this->getScoreProt();
}
