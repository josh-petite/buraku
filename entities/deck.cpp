//
// Created by Josh Petite on 2019-03-02.
//


#include <algorithm>
#include <random>
#include "deck.h"

deck::deck() {
  for (const auto faceValue : AllFaceValues) {
    for (const auto suit : AllSuits) {
      m_cards.emplace_back(card(suit, faceValue));
    }
  }
}

card deck::draw(int index) {
  auto it = std::next(m_cards.begin(), index);
  return *it;
}

void deck::shuffle() {
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(std::begin(m_cards), std::end(m_cards), g);
}
