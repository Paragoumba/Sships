#include "Logger.hpp"

Logger::Logger(){

    DEBUG_BUFFER_SIZE = Properties::DEBUG_H - 2;

    debugBuffer = new std::string*[DEBUG_BUFFER_SIZE];

    debugWin = newwin(Properties::DEBUG_H, Properties::DEBUG_W, Properties::TRAY_H, 0);
    box(debugWin, 0, 0);
    wrefresh(debugWin);

    mvwprintw(debugWin, 0, 2, " LOG ");
    wrefresh(debugWin);

}

void Logger::log(const char* string){

    bool added = false;

    for (int i = 0; i < DEBUG_BUFFER_SIZE; ++i){

        if (debugBuffer[i] == nullptr){

            debugBuffer[i] = new std::string(string);
            added = true;
            break;

        }
    }

    if (!added){

        for (int i = 0; i < DEBUG_BUFFER_SIZE - 1; ++i){

            debugBuffer[i] = debugBuffer[i + 1];

        }

        debugBuffer[DEBUG_BUFFER_SIZE - 1] = new std::string(string);

    }

    display();

}

void Logger::clear(){

    for (int i = 0; i < DEBUG_BUFFER_SIZE; ++i){

        delete(debugBuffer[i]);
        debugBuffer[i] = nullptr;

    }

    display();

}

void Logger::display(){

    for (int i = 0; i < DEBUG_BUFFER_SIZE; ++i){

        int size = 0;

        if (debugBuffer[i] != nullptr){

            mvwprintw(debugWin, i + 1, 1, debugBuffer[i]->c_str());
            size = int(debugBuffer[i]->length());

        } else {

            mvwprintw(debugWin, i + 1, 1, "");

        }

        for (int j = size + 1; j < COLS - 1; ++j){

            mvwaddch(debugWin, i + 1, j, ' ');

        }
    }

    wrefresh(debugWin);

}

Logger::~Logger(){

    delwin(debugWin);

}

int Logger::DEBUG_BUFFER_SIZE;