//
// Created by Josh Petite on 2019-03-02.
//

#include "Deck.h"

void Deck::Init() {
  int idx = 0;

  for (const auto faceValue : AllFaceValues) {
    for (const auto suit : AllSuits) {
      m_cards[idx] = Card(suit, faceValue);
      idx++;
    }
  }
}

Card Deck::Draw() {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist(0, CARD_COUNT - 1);

  int idx = dist(generator);
  return m_cards[idx];
}
