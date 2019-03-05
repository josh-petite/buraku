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

  std::cout << std::endl;

  m_user = std::make_shared<user>(name, STARTING_CHIPS);
}

bool game::atLeastOnePlayerIsNotStanding() const {
  return !m_dealer->standing() || !m_user->standing();
}

void game::awaitUserInput() const {
  std::cout << "Press enter key to continue...";
  std::cin.ignore(256,'\n');
  std::cin.get();
  std::cout << std::endl << std::endl;
}

void game::cleanup() {
  m_user->reset();
  m_dealer->reset();
}

char game::collectUserInput() {
  if (m_user->standing()) {
    return 's';
  }

  std::cout << "[b]et, [d]ouble-down, [h]it, [s]tay, [q]uit: " << std::endl;

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

void game::declareWinner() const {
  if (!m_playing) {
    return;
  }

  int userScore = m_user->getScore();
  int dealerScore = m_dealer->getScore();

  std::string hr = "------------------------------------------------";
  std::ostringstream os;

  printGameState(true);

  os << std::endl << "*** ";

  if (m_user->hasBlackjack()) {
    os << "B-L-A-C-K-J-A-C-K!! You won!";
    m_user->increaseWinstreak();
  }
  else if (m_dealer->hasBlackjack()) {
    os << m_dealer->getName() << " hit a blackjack *sad trombone*";
    m_user->resetWinstreak();
  }
  else if (m_user->busted()) {
    os << "You busted. Better luck next time!";
    m_user->resetWinstreak();
  }
  else if (m_dealer->busted()) {
    os << m_dealer->getName() << " busted. You won!";
    m_user->increaseWinstreak();
  }
  else if (userScore > dealerScore) {
    os << "You won!";
    m_user->increaseWinstreak();
  }
  else if (userScore < dealerScore) {
    os << m_dealer->getName() << " wins. Better luck next time!";
    m_user->resetWinstreak();
  }
  else if (userScore == dealerScore) {
    os << "You pushed with the dealer!";
  }

  os << " ***" << std::endl << hr << std::endl << std::endl;

  std::cout << os.str();

  awaitUserInput();
}

void game::doubleDown(std::shared_ptr<player> p) {
  p->setDoublingDown(true);
  m_dealer->dealCardTo(p.get());
  p->setStanding(true);
}

bool game::playersCanStillDrawCards() const {
  return m_playing
    && noOneHasBusted()
    && atLeastOnePlayerIsNotStanding()
    && noOneHasBlackjack();
}

bool game::noOneHasBusted() const {
  return !m_dealer->busted() && !m_user->busted();
}

bool game::noOneHasBlackjack() const {
  return !m_dealer->hasBlackjack() && !m_user->hasBlackjack();
}

int game::placeBets() {
  return 0;
}

void game::printGameState(bool gameOver) const {
  std::ostringstream os;

  os << std::endl;

  if (gameOver) {
    os << "------------------ Round Over ------------------" << std::endl;
  }

  os << m_dealer->getStatus(gameOver);
  os << m_user->getStatus();

  std::cout << os.str();
}

void game::printGameSummary(int round) const {
  std::cout << std::endl << std::endl;
  std::cout << "Rounds played: " << round << std::endl;
  std::cout << "Chip total: " << m_user->getChipTotal() << std::endl;
  std::cout << "------------------------------------------------" << std::endl << std::endl;
  std::cout << "Thanks for playing!" << std::endl;
}

void game::processRound(int round) {
  cleanup();
  int chipsInPot = placeBets();
  dealCards();

  int pass = 1;

  while (playersCanStillDrawCards()) {
    std::cout << "Round #" << round << ", Pass #" << pass << std::endl;
    std::cout << "Chips in pot: " << chipsInPot << std::endl;

    printGameState(false);
    processUserInput();
    m_dealer->takeAction(m_user);
    pass++;
  }

  declareWinner();
}

void game::processUserInput() {
  char input = collectUserInput();

  switch(input) {
    case 'b':
      //placeBet(m_user);
      break;
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
  int round = 1;

  while(m_playing) {
    processRound(round);
    round++;
  }

  printGameSummary(round);
}