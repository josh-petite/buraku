cmake_minimum_required(VERSION 3.13)
project(buraku)

set(CMAKE_CXX_STANDARD 17)

add_executable(buraku main.cpp entities/Card.cpp entities/Card.h entities/Suit.h entities/FaceValue.h)