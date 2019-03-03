//
// Created by Josh Petite on 2019-03-02.
//

#include "Card.h"

FaceValue Card::getValue() const {
  return m_value;
}

Suit Card::getSuit() const {
  return m_suit;
}