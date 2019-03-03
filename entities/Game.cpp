//
// Created by Josh Petite on 2019-03-03.
//

#include "Game.h"

Game::Game(const std::shared_ptr <Player> player) {
  m_player = player;
  m_dealer = std::make_shared<Dealer>();

  m_playing = false;
}

void Game::start() {
  m_playing = true;

  while(m_playing) {
    // deal initial cards
    // loop across players
    // get player input
    // if hit, deal, else

  }
}