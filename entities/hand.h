//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_HAND_H
#define BURAKU_HAND_H

#include <string>
#include <vector>
#include "card.h"

class hand {
public:
  hand() = default;

  void addCard(const card& card);
  bool busted() const;
  void discard();
  std::string getCurrentState() const;
  std::vector<std::string> getHandForDisplay() const;
  int getScore() const;
  bool hasBlackjack() const;
private:
  int calculateScoreWithAces(int score, int numberOfAces) const;

  std::vector<card> m_hand;
};


#endif //BURAKU_HAND_H
