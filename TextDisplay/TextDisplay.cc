#include "TextDisplay.h"
#include <string>
#include "../ObserverSubject/Subject.h"
#include "../Messaging/Messaging.h"
#include "../Enumerations/Direction.h"

TextDisplay::TextDisplay() {
}

TextDisplay::TextDisplay(std::vector<int> gridSize):
    gridSize {gridSize}
    {
        for (int i = 0; i < gridSize[0]; ++i) {
            theDisplay.push_back(std::vector<char>());
            for (int j = 0; j < gridSize[1]; ++j) {
                theDisplay[i].push_back(' ');
            }
        }
    }


void TextDisplay::setGridSize(std::vector<int> size) {
    gridSize = size;
    for (int i = 0; i < gridSize[0]; ++i) {
        theDisplay.push_back(std::vector<char>());
        for (int j = 0; j < gridSize[1]; ++j) {
            theDisplay[i].push_back(' ');
        }
    }
}

void TextDisplay::notify(Subject &notifier) {
    info = notifier.getInfo();
    theDisplay[info.coordinates[0]][info.coordinates[1]] = info.displayChar;
    std::cout << info.coordinates[0] << " " << info.coordinates[1] << " " << info.displayChar << std::endl;
    log << info.lastAction;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (auto &row: td.theDisplay) {
        for (auto &c: row) {
            out << c;
        }
        out << std::endl;
    }

    out << "Race: " << raceToText(td.info.race) << " Gold: " << td.info.gold << std::endl;
    out << "HP: " << td.info.HP << std::endl;
    out << "Atk: " << td.info.attackValue << std::endl;
    out << "Def: " << td.info.defenceValue << std::endl;
    out << "Action: " << td.info.lastAction << std::endl;

    return out;
}
