#include "Game.hpp"

#define CHECKED_CHAR "✓"
#define NOT_CHECKED_CHAR "⨯"

Game* Game::instance;

Game::Game(){

    ships[0] = new Ship(new Point(Point::B, Point::ONE), Ship::ShipType::DESTROYER);
    ships[1] = new Ship(new Point(Point::G, Point::ONE), Ship::ShipType::SUBMARINE);
    ships[2] = new Ship(new Point(Point::B, Point::THREE), Ship::ShipType::CRUISER);
    ships[3] = new Ship(new Point(Point::F, Point::THREE), Ship::ShipType::BATTLESHIP);
    ships[4] = new Ship(new Point(Point::B, Point::FIVE), Ship::ShipType::CARRIER);

    listWin = newwin(Properties::SHIP_LIST_H, Properties::SHIP_LIST_W, 0, 0);
    trayWin = newwin(Properties::TRAY_H, Properties::TRAY_W, 0, Properties::SHIP_LIST_W);

    logger = new Logger();

    box(listWin, 0, 0);
    box(trayWin, 0, 0);
    wrefresh(listWin);
    wrefresh(trayWin);

}

void Game::display() const {

    Tray tray = new char*[10];

    for (int i = 0; i < 10; ++i){

        tray[i] = new char[10];

        for (int j = 0; j < 10; ++j){

            tray[i][j] = ' ';

        }
    }

    for (Ship* ship : ships){

        ship->render(tray);

    }

    std::string shipsStr = " SHIPS ";

    mvwprintw(listWin, 0, (int) (Properties::SHIP_LIST_W - shipsStr.size()) / 2, shipsStr.c_str());
    //attron(COLOR_PAIR(SELECTED));
    mvwprintw(listWin, 2, 2, "1: ##");
    mvwprintw(listWin, 2, Properties::SHIP_LIST_PLACED_POSITION, selectedShip == Keys::K_ONE ? CHECKED_CHAR : NOT_CHECKED_CHAR);
    mvwprintw(listWin, 3, 2, "2: ###");
    mvwprintw(listWin, 3, Properties::SHIP_LIST_PLACED_POSITION, selectedShip == Keys::K_TWO ? CHECKED_CHAR : NOT_CHECKED_CHAR);
    mvwprintw(listWin, 4, 2, "3: ###");
    mvwprintw(listWin, 4, Properties::SHIP_LIST_PLACED_POSITION, selectedShip == Keys::K_THREE ? CHECKED_CHAR : NOT_CHECKED_CHAR);
    mvwprintw(listWin, 5, 2, "4: ####");
    mvwprintw(listWin, 5, Properties::SHIP_LIST_PLACED_POSITION, selectedShip == Keys::K_FOUR ? CHECKED_CHAR : NOT_CHECKED_CHAR);
    mvwprintw(listWin, 6, 2, "5: #####");
    mvwprintw(listWin, 6, Properties::SHIP_LIST_PLACED_POSITION, selectedShip == Keys::K_FIVE ? CHECKED_CHAR : NOT_CHECKED_CHAR);
    wrefresh(listWin);
    //attroff(COLOR_PAIR(SELECTED));

    int y = (int) (((float) Properties::TRAY_H - 23.0f) / 2);
    int x = 2 * y;

    // ─│┌┐└┘├┤┬┴┼ 🗸✓

    mvwprintw(trayWin, y, x,      "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐");
    mvwprintw(trayWin, y + 1, x,  "│ # │ A │ B │ C │ D │ E │ F │ G │ H │ I │ J │");
    mvwprintw(trayWin, y + 2, x,  "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 3, x,  "│ 0 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::ZERO], tray[Point::B][Point::ZERO], tray[Point::C][Point::ZERO], tray[Point::D][Point::ZERO], tray[Point::E][Point::ZERO], tray[Point::F][Point::ZERO], tray[Point::G][Point::ZERO], tray[Point::H][Point::ZERO], tray[Point::I][Point::ZERO], tray[Point::J][Point::ZERO]);
    mvwprintw(trayWin, y + 4, x,  "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 5, x,  "│ 1 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::ONE], tray[Point::B][Point::ONE], tray[Point::C][Point::ONE], tray[Point::D][Point::ONE], tray[Point::E][Point::ONE], tray[Point::F][Point::ONE], tray[Point::G][Point::ONE], tray[Point::H][Point::ONE], tray[Point::I][Point::ONE], tray[Point::J][Point::ONE]);
    mvwprintw(trayWin, y + 6, x,  "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 7, x,  "│ 2 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::TWO], tray[Point::B][Point::TWO], tray[Point::C][Point::TWO], tray[Point::D][Point::TWO], tray[Point::E][Point::TWO], tray[Point::F][Point::TWO], tray[Point::G][Point::TWO], tray[Point::H][Point::TWO], tray[Point::I][Point::TWO], tray[Point::J][Point::TWO]);
    mvwprintw(trayWin, y + 8, x,  "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 9, x,  "│ 3 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::THREE], tray[Point::B][Point::THREE], tray[Point::C][Point::THREE], tray[Point::D][Point::THREE], tray[Point::E][Point::THREE], tray[Point::F][Point::THREE], tray[Point::G][Point::THREE], tray[Point::H][Point::THREE], tray[Point::I][Point::THREE], tray[Point::J][Point::THREE]);
    mvwprintw(trayWin, y + 10, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 11, x, "│ 4 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::FOUR], tray[Point::B][Point::FOUR], tray[Point::C][Point::FOUR], tray[Point::D][Point::FOUR], tray[Point::E][Point::FOUR], tray[Point::F][Point::FOUR], tray[Point::G][Point::FOUR], tray[Point::H][Point::FOUR], tray[Point::I][Point::FOUR], tray[Point::J][Point::FOUR]);
    mvwprintw(trayWin, y + 12, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 13, x, "│ 5 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::FIVE], tray[Point::B][Point::FIVE], tray[Point::C][Point::FIVE], tray[Point::D][Point::FIVE], tray[Point::E][Point::FIVE], tray[Point::F][Point::FIVE], tray[Point::G][Point::FIVE], tray[Point::H][Point::FIVE], tray[Point::I][Point::FIVE], tray[Point::J][Point::FIVE]);
    mvwprintw(trayWin, y + 14, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 15, x, "│ 6 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::SIX], tray[Point::B][Point::SIX], tray[Point::C][Point::SIX], tray[Point::D][Point::SIX], tray[Point::E][Point::SIX], tray[Point::F][Point::SIX], tray[Point::G][Point::SIX], tray[Point::H][Point::SIX], tray[Point::I][Point::SIX], tray[Point::J][Point::SIX]);
    mvwprintw(trayWin, y + 16, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 17, x, "│ 7 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::SEVEN], tray[Point::B][Point::SEVEN], tray[Point::C][Point::SEVEN], tray[Point::D][Point::SEVEN], tray[Point::E][Point::SEVEN], tray[Point::F][Point::SEVEN], tray[Point::G][Point::SEVEN], tray[Point::H][Point::SEVEN], tray[Point::I][Point::SEVEN], tray[Point::J][Point::SEVEN]);
    mvwprintw(trayWin, y + 18, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 19, x, "│ 8 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::EIGHT], tray[Point::B][Point::EIGHT], tray[Point::C][Point::EIGHT], tray[Point::D][Point::EIGHT], tray[Point::E][Point::EIGHT], tray[Point::F][Point::EIGHT], tray[Point::G][Point::EIGHT], tray[Point::H][Point::EIGHT], tray[Point::I][Point::EIGHT], tray[Point::J][Point::EIGHT]);
    mvwprintw(trayWin, y + 20, x, "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤");
    mvwprintw(trayWin, y + 21, x, "│ 9 │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │ %c │", tray[Point::A][Point::NINE], tray[Point::B][Point::NINE], tray[Point::C][Point::NINE], tray[Point::D][Point::NINE], tray[Point::E][Point::NINE], tray[Point::F][Point::NINE], tray[Point::G][Point::NINE], tray[Point::H][Point::NINE], tray[Point::I][Point::NINE], tray[Point::J][Point::NINE]);
    mvwprintw(trayWin, y + 22, x, "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘");
    wrefresh(trayWin);

    for (int i = 0; i < 10; ++i){

        delete tray[i];

    }

    delete[] tray;

}

Game* Game::getInstance(){

    return instance;

}

void Game::mainLoop(){

    display();

    while (running){

        update();
        display();

    }
}

Logger *Game::getLogger() const {

    return logger;

}

void Game::setSelectedShip(int i){

    selectedShip = i;

}

bool Game::setShip(Ship::ShipType type, Point* firstPoint, Ship::Direction direction){

    for (auto& ship : ships){

        if (ship->getType() == type){

            if (Ship::isValid(firstPoint, type, direction)){

                ship->setFirstPoint(firstPoint);
                ship->setDirection(direction);

                return true;

            } else {

                return false;

            }
        }
    }

    return false;

}

void Game::stop(){

    running = false;

}

Game::~Game(){

    delwin(trayWin);
    delwin(listWin);

}
