#include "TextDisplay.h"
#include <string>
#include "../ObserverSubject/Subject.h"
#include "../Messaging/Messaging.h"
#include "../Enumerations/Direction.h"

TextDisplay::TextDisplay(std::vector<int> gridSize):
    gridSize {gridSize},
    theDisplay {std::vector<std::vector<char>>()},
    log {std::stringstream()},
    info {Info()}
    {}

void TextDisplay::notify(Subject &notifier) {
    info = notifier.getInfo();
    theDisplay[info.coordinates[0]][info.coordinates[1]] = info.displayChar;
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
