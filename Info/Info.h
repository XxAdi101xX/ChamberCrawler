#ifndef __INFO_H__
#define __INFO_H__

#include <string>
#include <vector>
#include "../Enumerations/Race.h"

struct Info {
	Race race;
	int gold;
	int HP;
	int attackValue;
	int defenceValue;

	std::vector<int> coordinates;
	char displayChar;
	std::string lastAction;

	bool isCellInfo = false;
};


#endif
