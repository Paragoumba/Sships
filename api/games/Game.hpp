#ifndef BATTLESHIP_GAME_HPP
#define BATTLESHIP_GAME_HPP

#include <ncurses.h>
#include <vector>
#include <string>

#include "../Logger.hpp"
#include "../ships/Ship.hpp"

#define SELECTED 1

typedef WINDOW* Window;
typedef char** Tray;

class Game {
public:
    static const int SHIP_NUMBER = 5;

    static Game* getInstance();

    void mainLoop();
    [[nodiscard]] Logger* getLogger() const;
    void setSelectedShip(int i);
    bool setShip(Ship::ShipType type, Point* firstPoint, Ship::Direction direction);
    virtual void update() = 0;
    void display() const;
    void stop();

    virtual ~Game();

protected:
    static Game* instance;

    bool running = true;
    Logger* logger;
    Window listWin;
    Window trayWin;

    int selectedShip = 0;

    Ship* ships[SHIP_NUMBER]{};

    Game();
};

#endif //BATTLESHIP_GAME_HPP
