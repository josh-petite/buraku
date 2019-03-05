//
// Created by Josh Petite on 2019-03-03.
//

#include <sstream>
#include "hand.h"

void hand::addCard(const card &c) {
  m_hand.push_back(c);
}

bool hand::busted() const {
  return getScore() > 21;
}

int hand::calculateScoreWithAces(int score, int numberOfAces) const {
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

void hand::discard() {
  m_hand.clear();
}

std::vector<std::string> hand::getHandForDisplay() const {
  std::vector<std::string> result;

  for (auto const& card : m_hand) {
    std::ostringstream os;
    os << card.deriveValueForDisplay() << card.deriveSuitForDisplay();
    result.push_back(os.str());
  }

  return result;
}

bool hand::hasBlackjack() const {
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

int hand::getScore() const {
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