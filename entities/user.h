//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_USER_H
#define BURAKU_USER_H


#include "player.h"

class user : public player {
public:
  // referenced via make_shared call in game.cpp
  user(std::string name, int startingChips) : player(std::move(name), startingChips) {}

  std::string getStatus() override;
  void reset() override;
};


#endif //BURAKU_USER_H
