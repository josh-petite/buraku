//
// Created by Josh Petite on 2019-03-03.
//

#include "user.h"

std::string user::getStatus() {
  std::ostringstream stream;
  std::string winStreak = getWinStreak() > 0
      ? (" (Win Streak: " + std::to_string(getWinStreak()) + ")")
      : "";

  stream << getName() << winStreak << std::endl;
  stream << "\tHand: ";

  for (auto const& c : m_hand->getHandForDisplay()) {
    stream << c << " ";
  }

  stream << std::endl;
  stream << "\tChips: " << getChipTotal() << std::endl;
  stream << "\t" << getCurrentState() << std::endl;

  return stream.str();
}

void user::processLoss() {
  resetWinStreak();
}

void user::processWin(int pot, bool wasBlackjack = false) {
  auto reward = static_cast<int>(pot * (wasBlackjack ? 2.5 : 2));
  addToChipTotal(reward);
  increaseWinStreak();
}

void user::reset() {
  resetRound();
  setDoublingDown(false);
  setStanding(false);
}