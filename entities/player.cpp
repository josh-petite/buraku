//
// Created by Josh Petite on 2019-03-03.
//

#include <sstream>
#include <iomanip>
#include "player.h"

void player::addToChipTotal(int chips) {
  m_chipTotal += chips;
}

int player::calculateScoreWithAces(int score, int numberOfAces) const {
  if (numberOfAces == 0) return score;

  if (numberOfAces == 1) {
    if (score <= 10) {
      return score + 11;
    }

    return score + 1;
  }

  int usingOneAceAtEleven = score + 11 + numberOfAces - 1;
  if (usingOneAceAtEleven <= 21) {
    return usingOneAceAtEleven;
  }

  return score + numberOfAces;
}

void player::discardHand() {
  m_hand.clear();
  m_standing = false;
  m_doublingDown = false;
}

int player::getChipTotal() const {
  return m_chipTotal;
}

int player::getCurrentBet() const {
  return m_currentBet;
}

int player::getCurrentHandScore() const {
  int score = 0;
  int numberOfAces = 0;

  for (const auto& c : m_hand) {
    faceValue fv = c.getValue();
    if (fv == faceValue::Ace) {
      numberOfAces++;
    } else {
      score += c.deriveScoreValue();
    }
  }

  return calculateScoreWithAces(score, numberOfAces);
}

std::vector<card> player::getHand() const {
  return m_hand;
}

std::string player::getName() const {
  return m_name;
}

bool player::hasBlackjack() const {
  if (m_hand.size() > 2) {
    return false;
  }

  bool holdingAce = std::any_of(m_hand.cbegin(), m_hand.cend(),
      [&](const card &arg) { return arg.getValue() == faceValue::Ace; });

  if (!holdingAce) {
    return false;
  }

  auto predicate = [&](const card &arg) {
    faceValue cardFaceValue = arg.getValue();
    return cardFaceValue == faceValue::Ten
      || cardFaceValue == faceValue::Jack
      || cardFaceValue == faceValue::Queen
      || cardFaceValue == faceValue::King;
  };

  bool holdingFaceValueOfTenCard = std::any_of(m_hand.cbegin(), m_hand.cend(), predicate);

  return holdingAce && holdingFaceValueOfTenCard;
}

bool player::busted() const {
  return getCurrentHandScore() > 21;
}

bool player::isDoublingDown() const {
  return m_doublingDown;
}

bool player::standing() const {
  return m_standing;
}

void player::receiveCard(const card &card) {
  m_hand.push_back(card);
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

std::string getScore(const player* p) {
  std::ostringstream os;
  if (p->busted()) {
    os << "B-";
  } else if (p->standing()) {
    os << "S-";
  }

  os << std::to_string(p->getCurrentHandScore());
  return os.str();
}

std::ostream& operator<<(std::ostream& stream, const player* p) {
  for (auto const& card : p->getHand()) {
    stream << card << " ";
  }

  return stream << std::endl << std::setw(4) << "(" << getScore(p) << ")" << std::endl;
}