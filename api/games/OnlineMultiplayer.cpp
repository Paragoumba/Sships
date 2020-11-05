//
// Created by paragoumba on 16/10/2019.
//

#include "OnlineMultiplayer.hpp"

OnlineMultiplayer::OnlineMultiplayer() = default;

Game* OnlineMultiplayer::newInstance(){

    delete(instance);

    return instance = new OnlineMultiplayer();

}

void OnlineMultiplayer::update(){



}
