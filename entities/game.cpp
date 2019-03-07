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
  std::cin.get(name, 32);

  m_user = std::make_shared<user>(name, STARTING_CHIPS);
}

bool game::atLeastOnePlayerIsNotStanding() const {
  return !m_dealer->standing() || !m_user->standing();
}

void game::awaitUserInput() const {
  do
  {
    std::cout << "\nPress a key to continue...";
  } while (std::cin.get() != '\n');

  std::cout << std::endl << std::endl;
}

void game::cleanup() const {
  m_user->reset();
  m_dealer->reset();
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

  for (int i = 0; i < padding - (padding % 2 == 0 ? 1 : 0); i++) { os << decorator; }

  return os.str();
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

void game::placeBets() {
  int currentChips = m_user->getChipTotal();

  std::cout << std::endl;
  std::cout << "Current Chip Total: " << currentChips << std::endl << std::endl;
  std::cout << "How much will you add to the pot?" << std::endl;
  std::cout << "1. 5 chips" << std::endl;
  std::cout << "2. 10 chips" << std::endl;
  std::cout << "3. ALL IN!" << std::endl;
  std::cout << "> ";

  char input;
  std::cin >> input;

  switch(input) {
    case '1': {
      m_user->decreaseChipTotal(5);
      m_currentPot += 5;
      break;
    }
    case '2': {
      m_user->decreaseChipTotal(10);
      m_currentPot += 10;
      break;
    }
    case '3': {

      m_user->decreaseChipTotal(currentChips);
      m_currentPot += currentChips;
      break;
    }
    default:
      m_user->decreaseChipTotal(5);
      m_currentPot += 5;
  }
}

void game::printGameSummary(int round) const {
  std::cout << std::endl << std::endl;
  std::cout << "Rounds played: " << round << std::endl;
  std::cout << "Chip total: " << m_user->getChipTotal() << std::endl;
  std::cout << generateCenteredMessage();
  std::cout << std::endl << std::endl << "Thanks for playing!" << std::endl;
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

void game::processOutcome(int chipsInPot) const {
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

  awaitUserInput();
}

void game::processRound(int round) {
  cleanup();
  placeBets();
  dealCards();

  int pass = 1;

  while (playersCanStillDrawCards()) {
    displayRoundHeaderMessage(round, pass);
    std::cout << "Chips in pot: " << m_currentPot << std::endl;

    printPassState();
    processUserInput();
    m_dealer->takeAction(m_user);
    pass++;
  }

  processOutcome(m_currentPot);
}

void game::processUserInput() {
  if (m_user->standing()) {
    return;
  }

  std::cout << "[b]et, [d]ouble-down, [h]it, [s]tay, [q]uit > ";
  bool responseInvalid = false;

  do {
    switch((char) std::cin.get()) {
      case 'b':
        placeBets();
        break;
      case 'd':
        doubleDown();
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
        responseInvalid = true;
    }
  } while (responseInvalid);
}

void game::start() {
  m_playing = true;
  int round = 1;

  while(m_playing) {
    processRound(round);
    round++;
    m_currentPot = 0;
  }

  printGameSummary(round);
}