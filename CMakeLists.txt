cmake_minimum_required(VERSION 3.16)
project(BattleShip)

set(CMAKE_CXX_STANDARD 20)

#execute_process(COMMAND ncursesw6-config --libs OUTPUT_VARIABLE NCURSES_FLAGS)

add_subdirectory("${PROJECT_SOURCE_DIR}/server")
add_subdirectory("${PROJECT_SOURCE_DIR}/client")
add_subdirectory("${PROJECT_SOURCE_DIR}/api")