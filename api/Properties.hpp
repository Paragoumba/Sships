#ifndef BATTLESHIP_PROPERTIES_HPP
#define BATTLESHIP_PROPERTIES_HPP

#include <ncurses.h>
#include <cmath>

class Properties {
public:
    Properties() = delete;

    static bool DEBUG;
    static const int SHIP_LIST_W = 20;
    static int SHIP_LIST_H;
    static const int SHIP_LIST_PLACED_POSITION = SHIP_LIST_W - 3;
    static int TRAY_W;
    static int TRAY_H;
    static int DEBUG_W;
    static int DEBUG_H;

    static void init(){

        DEBUG_H = (int) round((double) LINES / 4);

        TRAY_W = COLS - Properties::SHIP_LIST_W;
        TRAY_H = LINES - DEBUG_H;

        SHIP_LIST_H = TRAY_H;

        DEBUG_W = COLS;

    }
};

#endif //BATTLESHIP_PROPERTIES_HPP
