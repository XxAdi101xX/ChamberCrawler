#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "../ObserverSubject/Observer.h"
#include <vector>
#include <iostream>
#include <sstream>

#include "../Enumerations/Race.h"

class Subject;

class TextDisplay : public Observer {
    std::vector<int> gridSize;

    std::vector<std::vector<char>> theDisplay;
    std::stringstream log;

    Race r;
    int gold;
    int HP;
    int attackValue;
    int defenseValue;


public:
    TextDisplay(std::vector<int> size);

    void notify(Subject &whoNotified) override;
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
