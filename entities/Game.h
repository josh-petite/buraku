//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_GAME_H
#define BURAKU_GAME_H


#include "Player.h"
#include "Dealer.h"

class Game {
public:
  explicit Game(std::shared_ptr<Player> player);
  void start();
private:
  bool m_playing;
  std::shared_ptr<Dealer> m_dealer;
  std::shared_ptr<Player> m_player;
};


#endif //BURAKU_GAME_H
