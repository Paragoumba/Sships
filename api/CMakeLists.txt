cmake_minimum_required(VERSION 3.16)

add_library(API
        games/Game.cpp
        games/LocalMultiplayer.cpp
        games/OnlineMultiplayer.cpp
        ships/Ship.cpp
        Point.cpp
        Logger.cpp
        Properties.cpp)

target_include_directories(API PUBLIC .)

target_link_libraries(API ncursesw)