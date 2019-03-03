//
// Created by Josh Petite on 2019-03-03.
//

#include "dealer.h"

dealer::dealer() {
  m_deck = std::make_shared<deck>();
}

card dealer::drawCard() {
  const card card = m_deck->draw(m_deckIndex);
  m_deckIndex++;

  return card;
}

void dealer::reset() {
  discardHand();
  m_deck->shuffle();
  m_deckIndex = 0;
}