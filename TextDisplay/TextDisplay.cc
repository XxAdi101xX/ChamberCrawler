#include "TextDisplay.h"
#include <string>

TextDisplay::TextDisplay(std::vector<int> gridSize):
    gridSize {gridSize},
    theDisplay {std::vector<std::vector<char>>()},
    log {std::stringstream()},
    r {Race::Shade},
    gold {0},
    HP {0},
    attackValue {0},
    defenseValue {0}
    {
        for (int i = 0; i < row; ++i) {
            theDisplay.push_back(std::vector<char>());
            for (int j = 0; j < col; ++j) {
                theDisplay.push_back(' ');
            }
        }
    }

void TextDisplay::notify(Subject &notifier) {
    std::string info = notifier.getInfo();
    theDisplay[info.coordinates()[0]][info.coordinates()[1]] = info.displayChar();
    log << info.lastAction();
}

std::ostream &operator<<(std::osteram &out, const TextDisplay &td) {
    for (auto &row: theDisplay) {
        for (auto &c: row) {
            out << c;
        }
        out << std::endl;
    }

    out << "Race: " << r << " Gold: " << gold << std::endl;
    out << "HP: " << HP << std::endl;
    out << "Atk: " << attackValue << std::endl;
    out << "Def: " << defenseValue << std::endl;
    out << "Action: " << log << std::endl;

    return out;
}
