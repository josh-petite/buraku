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
  m_currentPot = 0;

  askUserForName();
}

void game::askUserForName() {
  displayWelcomeMessage();
  std::cout << std::endl << "What is your name?" << std::endl;

  char name[32];
  std::cin.getline(name, 32);

  m_user = std::make_shared<user>(name, STARTING_CHIPS);
}

bool game::atLeastOnePlayerIsNotStanding() const {
  return !m_dealer->standing() || !m_user->standing();
}

void game::cleanup() {
  m_user->reset();
  m_dealer->reset();
  m_currentPot = 0;
}

void game::dealCards() const {
  m_dealer->dealCardTo(m_user.get());
  m_dealer->dealCardTo(m_dealer.get());
  m_dealer->dealCardTo(m_user.get());
  m_dealer->dealCardTo(m_dealer.get());
}

void game::displayRoundHeaderMessage(const int round, const int pass) const {
  std::cout << std::endl;
  std::cout << generateCenteredMessage("Round #" + std::to_string(round) + ", Pass #" + std::to_string(pass));
  std::cout << std::endl;
  std::cout << "Chips in pot: " << m_currentPot;
  std::cout << std::endl;
}

void game::displayWelcomeMessage() const {
  std::cout << generateCenteredMessage("Welcome to Blackjack (ブラクジャク)") << std::endl;
  std::cout << std::endl;
}

void game::doubleDown() {
  m_user->setDoublingDown(true);
  m_dealer->dealCardTo(m_user.get());
  m_user->setStanding(true);
}

std::string game::generateCenteredMessage(std::string message, char decorator) const {
  std::ostringstream os;
  if (message.length() == 0) {
    for (int i = 0; i < 80; i++) { os << decorator; }
    return os.str();
  }

  long padding = (80 - message.length()) / 2;

  for (int i = 0; i < padding - 1; i++) { os << decorator; }

  os << " " << message << " ";

  for (int i = 0; i < padding - 1; i++) { os << decorator; }

  return os.str();
}

bool game::noOneHasBusted() const {
  return !m_dealer->busted() && !m_user->busted();
}

bool game::noOneHasBlackjack() const {
  return !m_dealer->hasBlackjack() && !m_user->hasBlackjack();
}

void game::placeBets() {
  int currentChips = m_user->getChipTotal();

  std::ostringstream os;
  os << std::endl << "Chips: " << currentChips << std::endl << std::endl;
  os << "How much will you add to the pot?" << std::endl << std::endl;
  os << "1. 5 chips" << std::endl;
  os << "2. 10 chips" << std::endl;
  os << "3. ALL IN!" << std::endl;
  os << "(1) ";

  char response = promptUser(os, { '1', '2', '3', '\n', '\r'});

  if (response == '2') {
    m_user->decreaseChipTotal(10);
    m_currentPot += 10;
  } else if (response == '3') {
    m_user->decreaseChipTotal(currentChips);
    m_currentPot += currentChips;
  } else {
    m_user->decreaseChipTotal(5);
    m_currentPot += 5;
  }
}

bool game::playersCanStillDrawCards() const {
  return m_playing
         && noOneHasBusted()
         && atLeastOnePlayerIsNotStanding()
         && noOneHasBlackjack();
}

void game::printGameSummary(int round) const {
  std::ostringstream os;
  os << std::endl << std::endl;
  os << "Rounds played: " << round << std::endl;
  os << "Chip total: " << m_user->getChipTotal() << std::endl;
  os << generateCenteredMessage();
  os << std::endl << std::endl << "Thanks for playing!" << std::endl;

  std::cout << os.str();
}

void game::printPassState() const {
  std::ostringstream os;

  os << std::endl;
  os << m_dealer->getStatus(false);
  os << m_user->getStatus();
  os << std::endl;

  std::cout << os.str();
}

void game::printRoundSummary() const {
  std::ostringstream os;
  os << std::endl;
  os << generateCenteredMessage("Round Over") << std::endl;

  os << m_dealer->getStatus(true);
  os << m_user->getStatus();
  os << std::endl;

  std::cout << os.str();
}

void game::processOutcome(int chipsInPot) {
  if (!m_playing) {
    return;
  }

  printRoundSummary();

  std::ostringstream os;
  int userScore = m_user->getScore();
  int dealerScore = m_dealer->getScore();

  if ((m_user->hasBlackjack() && m_dealer->hasBlackjack()) || (userScore == dealerScore)) {
    os << generateCenteredMessage("You pushed with the dealer!", '*');
  }
  else if (m_user->hasBlackjack()) {
    os << generateCenteredMessage("B-L-A-C-K-J-A-C-K!! You won!", '*');
    m_user->processWin(chipsInPot, true);
  }
  else if (m_dealer->hasBlackjack()) {
    os << generateCenteredMessage(m_dealer->getName() + " hit a blackjack!!", '*');
    m_user->processLoss();
  }
  else if (m_user->busted()) {
    os << generateCenteredMessage("You busted. Better luck next time!", '*');
    m_user->processLoss();
  }
  else if (m_dealer->busted()) {
    os << generateCenteredMessage(m_dealer->getName() + " busted. You won!", '*');
    m_user->processWin(chipsInPot, false);
  }
  else if (userScore > dealerScore) {
    os << generateCenteredMessage("You won!", '*');
    m_user->processWin(chipsInPot, false);
  }
  else if (userScore < dealerScore) {
    os << generateCenteredMessage(m_dealer->getName() + " wins. Better luck next time!", '*');
    m_user->processLoss();
  }

  os << std::endl << generateCenteredMessage() << std::endl << std::endl;

  std::cout << os.str();

  if (m_user->getChipTotal() <= 0) {
    m_playing = false;
    std::cout << "Oh no, you're out of chips!!" << std::endl;
  }
}

void game::processRound(int round) {
  cleanup();
  placeBets();
  dealCards();

  int pass = 1;

  while (playersCanStillDrawCards()) {
    displayRoundHeaderMessage(round, pass++);
    printPassState();
    processUserInput();
    m_dealer->takeAction(m_user);
  }

  processOutcome(m_currentPot);
}

void game::processUserInput() {
  if (m_user->standing()) {
    return;
  }

  std::ostringstream os;
  os << "[b]et, [d]ouble-down, [h]it, [s]tay, [q]uit" << std::endl << "(s) ";

  char response = promptUser(os, { 'b', 'd', 'h', 'q', 's' });

  if (response == 'b') {
    placeBets();
  } else if (response == 'd') {
    doubleDown();
  } else if (response == 'h') {
    m_dealer->dealCardTo(m_user.get());
  } else if (response == 's') {
    m_user->setStanding(true);
  } else if (response == 'q'){
    m_playing = false;
  }
}

char game::promptUser(std::ostringstream& prompt, std::set<int> answers) const {
  std::cout << prompt.str();
  char response;

  do {
    std::cin >> std::setw(1) >> response;
  } while (answers.find(response) == answers.end());

  return response;
}

void game::start() {
  m_playing = true;
  int round = 1;

  while(m_playing) {
    processRound(round++);
  }

  printGameSummary(round);
}