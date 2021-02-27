/*  MCU List
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <vector>
#include "Tools/PersistentSettings.h"
#include "BoardList.h"


const std::vector<std::pair<std::string, QString>> BOARD_LIST{
    {"Teensy2", "Teensy 2.0"},
    {"TeensyPP2", "Teensy++ 2.0"},
    {"ProMicro", "Pro Micro"},
    {"ArduinoUnoR3", "Arduino Uno R3"},
};

BoardList::BoardList(QWidget& parent)
    : QComboBox(&parent)
{
    for (const auto& item : BOARD_LIST){
        addItem(item.second);
    }
    setCurrentIndex(settings.board_index);

    connect(
        this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){ settings.board_index = index; }
    );
}

const std::string& BoardList::get_board() const{
    return BOARD_LIST[currentIndex()].first;
}

