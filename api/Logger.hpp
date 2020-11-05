#ifndef BATTLESHIP_LOGGER_HPP
#define BATTLESHIP_LOGGER_HPP

#include <string>
#include <ncurses.h>

#include "Properties.hpp"

class Logger {
private:
    static int DEBUG_BUFFER_SIZE;

    WINDOW* debugWin;
    std::string** debugBuffer;

    ~Logger();

public:
    Logger();

    void log(const char* string);
    void clear();
    void display();
};

#endif //BATTLESHIP_LOGGER_HPP
