//
// Created by paragoumba on 16/10/2019.
//

#ifndef BATTLESHIP_ONLINEMULTIPLAYER_HPP
#define BATTLESHIP_ONLINEMULTIPLAYER_HPP

#include "Game.hpp"

class OnlineMultiplayer : private Game {
public:
    OnlineMultiplayer();

    static Game* newInstance();

    void update() override;
};

#endif //BATTLESHIP_ONLINEMULTIPLAYER_HPP
