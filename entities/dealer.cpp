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

std::string dealer::getStatus(bool gameOver) {
  std::ostringstream stream;
  stream << getName() << std::endl;
  stream << "\tHand: ";

  bool firstCardSkipped = gameOver;
  for (auto const& c : m_hand->getHandForDisplay()) {
    if (!firstCardSkipped) {
      stream << "H  ";
      firstCardSkipped = true;
      continue;
    }

    stream << c << " ";
  }

  stream << std::endl;
  stream << "\t" << getCurrentState() << std::endl;

  return stream.str();
}

void dealer::reset() {
  resetRound();
  setStanding(false);

  m_deck->shuffle();
  m_deckIndex = 0;
}

void dealer::takeAction(const std::shared_ptr<player> opponent) {
  if (standing()) {
    return;
  }

  int dealerScore = m_hand->getScore();
  if (dealerScore < 17) {
    dealCardTo(this);
    return;
  }

  if (!opponent->busted() && opponent->getScore() > dealerScore) {
    dealCardTo(this);
    return;
  }

  setStanding(true);
}