//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_GAME_H
#define BURAKU_GAME_H


#include "dealer.h"
#include "user.h"

class game {
public:
  game();

  void start();
private:
  void askUserForName();
  char collectUserInput();
  void dealCards();
  void dealCardTo(player& player);
  void drawGameState() const;
  void processUserInput(char input);
  void startRound();

  bool m_playing;
  std::shared_ptr<dealer> m_dealer;
  std::shared_ptr<user> m_user;
};


#endif //BURAKU_GAME_H
