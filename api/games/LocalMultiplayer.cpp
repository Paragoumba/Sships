#include "LocalMultiplayer.hpp"

Game *LocalMultiplayer::newInstance(){

    delete(instance);

    return instance = new LocalMultiplayer();

}

void LocalMultiplayer::update(){

    int charCode = getch();

    if (Properties::DEBUG && charCode != ERR){

        logger->log((std::string("CharCode ") + std::to_string(charCode)).c_str());

    }

    if (charCode == K_ONE || charCode == K_TWO || charCode == K_THREE ||
        charCode == K_FOUR || charCode == K_FIVE){

        selectedShip = charCode;

        logger->log((std::string("Placing ship ") + std::to_string(selectedShip - 48)).c_str());
        display();

        cbreak();
        logger->log("Enter x coordinate");
        charCode = getch();

        if (Point::isXCoordinate(charCode)){

            int x = charCode - 97;

            logger->log("Enter y coordinate");
            charCode = getch();

            if (Point::isYCoordinate(charCode)){

                int y = charCode - 48;

                logger->log("Enter direction (h)orizontal/(v)ertical");
                charCode = getch();

                if (charCode == K_V || charCode == K_H){

                    Ship::Direction direction = charCode == K_V ? Ship::Direction::VERTICAL : Ship::Direction::HORIZONTAL;

                    if (setShip(
                            Ship::getShipTypeForKey(Keys(selectedShip)),
                            new Point(Point::Letter(x), Point::Number(y)),
                            Ship::Direction(direction))){

                        logger->log(("Ship placed at (x:" + std::to_string(x) + " y:" + std::to_string(y) + ") d:" + direction).c_str());

                    } else {

                        logger->log(("Invalid position (x:" + std::to_string(x) + " y:" + std::to_string(y) + ") d:" + direction).c_str());

                    }

                } else {

                    logger->log("Error when trying to get direction");

                }

            } else {

                logger->log("Error when trying to get Y coordinate");

            }

        } else {

            logger->log("Error when trying to get X coordinate");

        }

        halfdelay(1);
        selectedShip = 0;

    } else if (charCode == K_ESC){

        if ((charCode = getch()) == ERR){

            running = false;

        } else if (charCode == 91 && (charCode = getch()) == K_SCROLL_WHEEL_UP){

            logger->log("Scroll wheel up");

        }

    } else if (charCode == K_C){

        logger->clear();

    } else if (charCode == K_D){

        logger->log((std::string("Screen size is ") + std::to_string(COLS) + "x" + std::to_string(LINES)).c_str());

    }
}
