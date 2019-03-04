//
// Created by Josh Petite on 2019-03-03.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include "game.h"

game::game() {
  m_dealer = std::make_shared<dealer>();
  m_playing = false;

  askUserForName();
}

void game::askUserForName() {
  std::cout << "What is your name?" << std::endl;

  std::string name;
  std::cin >> name;

  m_user = std::make_shared<user>(name, 100);
}

void game::cleanup() {
  m_user->reset();
  m_dealer->reset();
}

char game::collectUserInput() {
  if (m_user->standing()) {
    return 's';
  }

  std::cout << "[d]ouble down, [h]it, [s]tay, [q]uit: " << std::endl;

  char input;
  std::cin >> input;

  return input;
}

void game::dealCards() {
  m_dealer->dealCardTo(m_user.get());
  m_dealer->dealCardTo(m_dealer.get());
  m_dealer->dealCardTo(m_user.get());
  m_dealer->dealCardTo(m_dealer.get());
}

void game::declareWinner() {
  if (!m_playing) {
    return;
  }

  int userScore = m_user->getCurrentHandScore();
  int dealerScore = m_dealer->getCurrentHandScore();
  std::ostringstream os;

  os << std::endl << "------------------------------------------------";
  generateGameState(os);
  os << std::endl << "*** ";

  if (m_user->hasBlackjack()) {
    os << "B-L-A-C-K-J-A-C-K!! You won!";
  }
  else if (m_dealer->hasBlackjack()) {
    os << m_dealer->getName() << " wins. Better luck next time!";
  }
  else if (m_user->busted()) {
    os << "You busted. Better luck next time!";
  }
  else if (m_dealer->busted()) {
    os << m_dealer->getName() << " busted. You won!";
  }
  else if (userScore > dealerScore) {
    os << "You won!";
  }
  else if (userScore < dealerScore) {
    os << m_dealer->getName() << " wins. Better luck next time!";
  }
  else if (userScore == dealerScore) {
    os << "You pushed with the dealer!";
  }

  os << " ***" << std::endl << "------------------------------------------------" << std::endl << std::endl;
  std::cout << os.str();
}

void game::doubleDown(std::shared_ptr<player> p) {
  p->setDoublingDown(true);
  m_dealer->dealCardTo(p.get());
  p->setStanding(true);
}

void game::generateGameState(std::ostringstream& os) const {
  int longestNameLength = (int)std::max(m_dealer->getName().length(), m_user->getName().length());

  os << std::endl;
  os << std::setw(longestNameLength) << m_dealer->getName() << ": " << m_dealer;
  os << std::setw(longestNameLength) << m_user->getName() << ": " << m_user;
}

bool game::playersCanStillDrawCards() const {
  return m_playing
    && (!m_dealer->busted()     && !m_user->busted())
    && (!m_dealer->standing()   || !m_user->standing())
    && (!m_dealer->hasBlackjack() && !m_user->hasBlackjack());
}

void game::processUserInput() {
  char input = collectUserInput();

  switch(input) {
    case 'd':
      doubleDown(m_user);
      break;
    case 'h':
      m_dealer->dealCardTo(m_user.get());
      break;
    case 's':
      m_user->setStanding(true);
      break;
    case 'q':
      m_playing = false;
      break;
    default:
      std::cout << "Invalid selection. Please try again.";
  }
}

void game::start() {
  m_playing = true;

  while(m_playing) {
    cleanup();
    dealCards();

    while (playersCanStillDrawCards()) {
      std::ostringstream os;
      generateGameState(os);
      std::cout << os.str();
      processUserInput();
      m_dealer->takeAction(m_user);
      std::cout << std::endl;
    }

    declareWinner();
  }

  std::cout << "Thanks for playing!" << std::endl;
}