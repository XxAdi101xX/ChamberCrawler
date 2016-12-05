#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "../ObserverSubject/Observer.h"
#include <vector>
#include <iostream>
#include <sstream>

#include "../Enumerations/Race.h"
#include "../Info/Info.h"

class Subject;

class TextDisplay : public Observer {
    std::vector<int> gridSize;

    std::vector<std::vector<char>> theDisplay;
    std::stringstream log;

    Info info;
		int floorNumber = 1;

public:
    TextDisplay();
    TextDisplay(std::vector<int> size);

    void setGridSize(std::vector<int> size);

    void notify(Subject &whoNotified) override;
		
		void setFloorNumber(int floorNum);

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif
