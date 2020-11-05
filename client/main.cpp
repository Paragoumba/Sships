#include <csignal>
#include <iostream>
#include <cstring>
#include <games/Game.hpp>
#include <games/LocalMultiplayer.hpp>

void exitHandler(int){

    Game::getInstance()->stop();

}

int main(int argc, char** argv){

    signal(SIGINT, exitHandler);

    if (argc > 1 && !strcmp(argv[1], "debug")){

        Properties::DEBUG = true;

    }

    setlocale(LC_ALL, "");
    init_pair(SELECTED, COLOR_BLACK, COLOR_WHITE);

    initscr();
    start_color();
    curs_set(0);
    cbreak();
    noecho();
    halfdelay(1);
    refresh();

    Properties::init();

    Game* game = LocalMultiplayer::newInstance();

    game->mainLoop();

    delete game;

    endwin();

    return 0;

}
