//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_DECK_H
#define BURAKU_DECK_H


#include <random>
#include "card.h"

class deck {
public:
  deck() : m_cards() { init(); }

  card draw(int index);
  void shuffle();
private:
  void init();

  static const size_t CARD_COUNT = 52;
  card m_cards[CARD_COUNT];
};


#endif //BURAKU_DECK_H
