#ifndef BATTLESHIP_SHIP_HPP
#define BATTLESHIP_SHIP_HPP

#include <ncurses.h>
#include <string>

#include "../Point.hpp"
#include "../Keys.hpp"

class Ship {
public:
    enum class ShipType {
        CARRIER = 5,
        BATTLESHIP = 4,
        CRUISER = 3,
        SUBMARINE = 3,
        DESTROYER = 2
    };

    enum class Direction {
        HORIZONTAL = 0,
        VERTICAL = 1
    };

    static const char SHIP_PART = '#';
    static const char SHIP_PART_TOUCHED = '+';
    static const char SHIP_PART_SUNK = '@';
    static const char WATER_TOUCHED = '*';

    static ShipType getShipTypeForKey(Keys k);

    Ship(Point* origin, ShipType type);
    Ship(Point* origin, ShipType type, Direction direction);

    [[nodiscard]] ShipType getType() const;
    void setDirection(Direction direction);
    void setFirstPoint(Point* origin);
    static bool isValid(Point* origin, ShipType type, Direction direction);
    void render(char** tray) const;

    friend std::string operator+(const std::string& string, Ship::Direction direction);

protected:
    Point* origin;
    ShipType type;
    Direction direction;
    bool* touched;
};

#endif //BATTLESHIP_SHIP_HPP
