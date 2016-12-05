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
    theDisplay = std::vector<std::vector<char>>();
    for (int i = 0; i < gridSize[0]; ++i) {
        theDisplay.push_back(std::vector<char>());
        for (int j = 0; j < gridSize[1]; ++j) {
            theDisplay[i].push_back(' ');
        }
    }
}

void TextDisplay::notify(Subject &notifier) {
    Info i = notifier.getInfo();
    if (i.isCellInfo) {
        info.coordinates = i.coordinates;
        info.displayChar = i.displayChar;
        theDisplay[info.coordinates[0]][info.coordinates[1]] = info.displayChar;
    }
    else {

        info.lastAction = i.lastAction;
        info.race = i.race;
        info.gold = i.gold;
        info.HP = i.HP;
        info.attackValue = i.attackValue;
        info.defenceValue = i.defenceValue;
    }
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
