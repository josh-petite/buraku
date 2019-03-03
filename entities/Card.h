#include <utility>

//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_CARD_H
#define BURAKU_CARD_H

#include <string>
#include "Common.h"

class Card {
public:
  Card() {}
  Card(const Suit suit, const FaceValue value)
    : m_suit(suit), m_value(value) {}

  FaceValue GetValue() const;
  Suit GetSuit() const;
private:
  FaceValue m_value;
  Suit m_suit;
};


#endif //BURAKU_CARD_H
