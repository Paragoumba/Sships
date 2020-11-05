//
// Created by paragoumba on 03/10/2019.
//

#include "Point.hpp"
#include "Keys.hpp"

Point::Point(Letter letter, Number number) : letter(letter), number(number) {}

bool Point::isXCoordinate(int charcode){

    return charcode == K_A || charcode == K_B || charcode == K_C || charcode == K_D || charcode == K_E ||
           charcode == K_F || charcode == K_G || charcode == K_H || charcode == K_I || charcode == K_J;

}

bool Point::isYCoordinate(int charcode){

    return charcode == K_ZERO || charcode == K_ONE || charcode == K_TWO || charcode == K_THREE || charcode == K_FOUR || charcode == K_FIVE ||
           charcode == K_SIX || charcode == K_SEVEN || charcode == K_EIGHT || charcode == K_NINE;

}
