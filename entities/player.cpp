//
// Created by Josh Petite on 2019-03-03.
//

#include "player.h"

void player::addToChipTotal(int chips) {
  m_chipTotal += chips;
}

void player::discardHand() {
  m_hand->discard();
  m_standing = false;
  m_doublingDown = false;
}

int player::getChipTotal() const {
  return m_chipTotal;
}

int player::getCurrentBet() const {
  return m_currentBet;
}

std::string player::getCurrentState() const {
  std::ostringstream stream;

  if (busted()) {
    stream << "(busted)";
  } else if (standing()) {
    stream << "(standing)";
  }

  return stream.str();
}

std::string player::getName() const {
  return m_name;
}

std::string player::getStatus() {
  std::ostringstream stream;
  stream << getName() << std::endl;
  stream << "\tHand: ";

  bool firstCardSkipped = false;
  for (auto const& c : m_hand->getHandForDisplay()) {
    if (!firstCardSkipped) {
      stream << "H  ";
      firstCardSkipped = true;
      continue;
    }

    stream << c << " ";
  }

  stream << std::endl;
  stream << "\tChips: " << getChipTotal() << std::endl;
  stream << "\t" << getCurrentState() << std::endl;

  return stream.str();
}

bool player::isDoublingDown() const {
  return m_doublingDown;
}

bool player::standing() const {
  return m_standing;
}

void player::receiveCard(const card &card) {
  m_hand->addCard(card);
}

void player::setCurrentBet(int bet) {
  m_currentBet = bet;
}

void player::setDoublingDown(bool doublingDown) {
  m_doublingDown = doublingDown;
}

void player::setStanding(bool standing) {
  m_standing = standing;
}