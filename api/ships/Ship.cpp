#include "Ship.hpp"

Ship::ShipType Ship::getShipTypeForKey(Keys k){

    switch (k){

        case K_ONE:
            return Ship::ShipType::DESTROYER;

        case K_TWO:
            return Ship::ShipType::SUBMARINE;

        case K_THREE:
            return Ship::ShipType::CRUISER;

        case K_FOUR:
            return Ship::ShipType::BATTLESHIP;

        case K_FIVE:
            return Ship::ShipType::CARRIER;

        default:
            throw std::exception();

    }
}

Ship::Ship(Point *origin, Ship::ShipType type) : Ship(origin, type, Direction::HORIZONTAL) {}

Ship::Ship(Point* origin, ShipType type, Direction direction) :
        origin(origin), type(type), direction(direction), touched(new bool[int(type)]){

    int shipLength = int(type);

    for (int i = 0; i < shipLength; ++i){

        touched[i] = false;

    }
}

Ship::ShipType Ship::getType() const {

    return type;

}

void Ship::setDirection(Ship::Direction direction){

    this->direction = direction;

}

void Ship::setFirstPoint(Point* origin){

    this->origin = origin;

}

bool Ship::isValid(Point* origin, ShipType type, Direction direction){

    //return (direction == Direction::HORIZONTAL && origin->letter + int(type) <= 10) || (direction == Direction::VERTICAL && origin->number + int(type) <= 10);

    if (direction == Direction::HORIZONTAL){

        if (origin->letter + int(type) <= 10){

            return true;

        }

    } else if (direction == Direction::VERTICAL){

        if (origin->number + int(type) <= 10){

            return true;

        }
    }

    return false;

}

void Ship::render(char** tray) const {

    if (origin != nullptr){

        bool sunk = true;
        int shipLength = int(type);

        for (int i = 0; i < shipLength; ++i){

            int x = origin->letter;
            int y = origin->number;

            if (direction == Direction::HORIZONTAL){

                x = origin->letter + i;

            } else {

                y = origin->number + 1;

            }

            if (touched[i]){

                tray[x][y] = SHIP_PART_TOUCHED;

            } else {

                tray[x][y] = SHIP_PART;
                sunk = false;

            }
        }

        if (sunk){

            for (int i = 0; i < shipLength; ++i){

                int x = direction == Direction::HORIZONTAL ? origin->letter + i : origin->letter;
                int y = direction == Direction::HORIZONTAL ? origin->number : origin->number + i;

                tray[x][y] = SHIP_PART_SUNK;

            }
        }
    }
}

std::string operator+(const std::string& string, Ship::Direction direction){

    std::string temp = string + (direction == Ship::Direction::HORIZONTAL ? "HORIZONTAL" : "VERTICAL");

    return temp;

}
