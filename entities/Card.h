#include <utility>

//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_CARD_H
#define BURAKU_CARD_H

#include <string>
#include "Suit.h"
#include "FaceValue.h"

class Card {
public:
  Card(const Suit suit, const FaceValue value)
    : m_suit(suit), m_value(value) {}

  FaceValue getValue() const;
  Suit getSuit() const;
private:
  FaceValue m_value;
  Suit m_suit;
};


#endif //BURAKU_CARD_H
