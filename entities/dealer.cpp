//
// Created by Josh Petite on 2019-03-03.
//

#include "dealer.h"

card dealer::drawCard() {
  const card c = m_deck->draw(m_deckIndex);
  m_deckIndex++;

  return c;
}

void dealer::dealCardTo(player* p) {
  const card& c = drawCard();
  p->receiveCard(c);
}

void dealer::reset() {
  discardHand();
  setStanding(false);

  m_deck->shuffle();
  m_deckIndex = 0;
}

void dealer::takeAction(const std::shared_ptr<player> opponent) {
  if (standing()) {
    return;
  }

  int dealerScore = getCurrentHandScore();
  if (dealerScore < 17) {
    dealCardTo(this);
    return;
  }

  if (!opponent->busted() && opponent->getCurrentHandScore() > dealerScore) {
    dealCardTo(this);
    return;
  }

  setStanding(true);
}