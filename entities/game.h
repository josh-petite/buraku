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
  bool atLeastOnePlayerIsNotStanding() const;
  void awaitUserInput() const;
  void cleanup();
  char collectUserInput();
  void dealCards();
  void declareWinner() const;
  void doubleDown(std::shared_ptr<player> player);
  bool noOneHasBusted() const;
  bool noOneHasBlackjack() const;
  void placeBets();
  void printGameState(bool gameOver) const;
  bool playersCanStillDrawCards() const;
  void processRound();
  void processUserInput();

  bool m_playing;
  std::shared_ptr<dealer> m_dealer;
  std::shared_ptr<user> m_user;

  const int STARTING_CHIPS = 100;
};


#endif //BURAKU_GAME_H
