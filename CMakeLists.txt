cmake_minimum_required(VERSION 3.19)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minesweeper main.cpp Tile.h Bomb.h BombContainer.h Board.h)