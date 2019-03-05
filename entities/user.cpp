//
// Created by Josh Petite on 2019-03-03.
//

#include "user.h"

std::string user::getStatus() {
  std::ostringstream stream;
  std::string winStreak = getWinstreak() > 0
      ? (" (Win Streak: " + std::to_string(getWinstreak()) + ")")
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

void user::reset() {
  discardHand();
  setDoublingDown(false);
  setStanding(false);
}