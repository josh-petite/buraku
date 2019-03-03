#include <utility>

//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_PLAYER_H
#define BURAKU_PLAYER_H

#include <string>
#include <vector>
#include "Card.h"

class Player {
public:
  explicit Player(std::string name) : m_name(std::move(name)) {}
private:
  std::string m_name;
  std::vector<Card> m_hand;
};


#endif //BURAKU_PLAYER_H
