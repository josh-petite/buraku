//
// Created by Josh Petite on 2019-03-02.
//

#include "Card.h"

FaceValue Card::GetValue() const {
  return m_value;
}

Suit Card::GetSuit() const {
  return m_suit;
}