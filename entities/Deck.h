//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_DECK_H
#define BURAKU_DECK_H


#include <random>
#include "Card.h"

class Deck {
public:
  Deck() : m_cards() { Init(); }
  Card Draw();
private:
  void Init();

  static const size_t CARD_COUNT = 52;
  Card m_cards[CARD_COUNT];
};


#endif //BURAKU_DECK_H
