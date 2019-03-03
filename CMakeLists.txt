cmake_minimum_required(VERSION 3.13)
project(buraku)

set(CMAKE_CXX_STANDARD 17)

add_executable(buraku main.cpp entities/Card.cpp entities/Card.h enums/Suit.h enums/FaceValue.h entities/Deck.cpp entities/Deck.h entities/Game.cpp entities/Game.h entities/Player.cpp entities/Player.h entities/Dealer.cpp entities/Dealer.h entities/Common.h)