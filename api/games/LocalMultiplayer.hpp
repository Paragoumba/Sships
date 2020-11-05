//
// Created by paragoumba on 10/10/2019.
//

#ifndef BATTLESHIP_LOCALMULTIPLAYER_HPP
#define BATTLESHIP_LOCALMULTIPLAYER_HPP

#include "Game.hpp"

class LocalMultiplayer : private Game {
public:
    static Game* newInstance();

    std::vector<Point*> allyHits;
    std::vector<Point*> enemyHits;

    void update() override;
};

#endif //BATTLESHIP_LOCALMULTIPLAYER_HPP
