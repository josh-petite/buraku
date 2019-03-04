#include <utility>

//
// Created by Josh Petite on 2019-03-02.
//

#ifndef BURAKU_CARD_H
#define BURAKU_CARD_H

#include <iostream>
#include <string>
#include "common.h"

class card {
public:
  card() = default;
  card(const suit suit, const faceValue value)
    : m_suit(suit), m_value(value) {}

  int deriveScoreValue() const;
  faceValue getValue() const;
  suit getSuit() const;
private:
  faceValue m_value;
  suit m_suit;
};

std::ostream& operator<<(std::ostream& stream, const card& card);


#endif //BURAKU_CARD_H
