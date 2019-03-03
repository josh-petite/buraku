//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_PLAYER_H
#define BURAKU_PLAYER_H


#include <string>
#include <utility>
#include <vector>
#include "card.h"

class player {
public:
  player() = default;

  std::string describeHand() const;
  void discardHand();
  std::string getName();
  void receiveCard(const card &card);
  void setName(std::string name);
private:
  std::string m_name;
  std::vector<card> m_hand;
};

std::ostream& operator<<(std::ostream& stream, const player& player);


#endif //BURAKU_PLAYER_H
