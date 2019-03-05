//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_DECK_H
#define BURAKU_DECK_H


#include <random>
#include <vector>
#include "card.h"

class deck {
public:
  deck();

  card draw(int index);
  void shuffle();
private:
  std::vector<card> m_cards;
};


#endif //BURAKU_DECK_H
