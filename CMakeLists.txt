cmake_minimum_required(VERSION 3.13)
project(buraku)

set(CMAKE_CXX_STANDARD 17)

add_executable(buraku main.cpp entities/card.cpp entities/card.h enums/suit.h enums/faceValue.h entities/deck.cpp entities/deck.h entities/game.cpp entities/game.h entities/player.cpp entities/player.h entities/dealer.cpp entities/dealer.h entities/common.h entities/user.cpp entities/user.h entities/hand.cpp entities/hand.h)