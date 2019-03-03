//
// Created by Josh Petite on 2019-03-03.
//

#include <iostream>
#include "game.h"

game::game() {
  m_user = std::make_shared<user>();
  m_dealer = std::make_shared<dealer>();

  m_playing = false;

  askUserForName();
}

void game::askUserForName() {
  std::cout << "What is your name?" << std::endl;

  std::string name;
  std::cin >> name;

  m_user->setName(name);
}

void game::start() {
  m_playing = true;

  while(m_playing) {
    startRound();
    dealCards();
    drawGameState();
    // loop across players, collect input
    char input = collectUserInput();
    processUserInput(input);
    // loop until all players stay
    // calculate totals
    // declare winner
  }
}

char game::collectUserInput() {
  std::cout << "[h]it -- [s]tay -- [q]uit" << std::endl;
  std::cout << ": ";

  char input;
  std::cin >> input;

  return input;
}

void game::dealCards() {
  dealCardTo(*m_user);
  dealCardTo(*m_dealer);
  dealCardTo(*m_user);
  dealCardTo(*m_dealer);
}

void game::drawGameState() const {
  std::cout << "Dealer: " << *m_dealer << std::endl;
  std::cout << m_user->getName() << ": \t" << *m_user << std::endl;
}

void game::processUserInput(char input) {
  switch(input) {
    case 'h':
      dealCardTo(*m_user);
      break;
    case 's':
      break;
    case 'q':
      m_playing = false;
      break;
    default:
      std::cout << "Invalid selection. Please try again.";
  }
}

void game::dealCardTo(player& player) {
  const card& c = m_dealer->drawCard();
  player.receiveCard(c);
}

void game::startRound() {
  m_user->discardHand();
  m_dealer->reset();
}