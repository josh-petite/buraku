//
// Created by Josh Petite on 2019-03-02.
//

#include "deck.h"

void deck::init() {
  int idx = -1;

  for (const auto faceValue : AllFaceValues) {
    for (const auto suit : AllSuits) {
      m_cards[idx++] = card(suit, faceValue);
    }
  }
}

card deck::draw(int index) {
  return m_cards[index];
}

void deck::shuffle() {
  std::random_device rd;
  std::default_random_engine engine{rd()};
  std::uniform_int_distribution<int> distribution(0, CARD_COUNT - 1);

  auto randomIndex = std::bind(distribution, engine);

  for (int i = 0; i < 1000; i++) {
    int source = randomIndex();
    card temp = m_cards[i % CARD_COUNT];
    m_cards[i % CARD_COUNT] = m_cards[source];
    m_cards[source] = temp;
  }
}
