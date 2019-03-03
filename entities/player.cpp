//
// Created by Josh Petite on 2019-03-03.
//

#include <sstream>
#include "player.h"

std::string player::describeHand() const {
  std::ostringstream os;

  for (auto const& card : m_hand) {
    os << card << " ";
  }

  return os.str();
}

void player::discardHand() {
  m_hand.clear();
}

std::string player::getName() {
  return m_name;
}

void player::receiveCard(const card &card) {
  m_hand.push_back(card);
}

void player::setName(const std::string name) {
  m_name = name;
}

std::ostream& operator<<(std::ostream& stream, const player& player) {
  return stream << player.describeHand();
}