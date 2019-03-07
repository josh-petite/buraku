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
  void cleanup() const;
  void dealCards() const;
  void displayRoundHeaderMessage(int round, int pass) const;
  void displayWelcomeMessage() const;
  void doubleDown();
  std::string generateCenteredMessage(std::string message = "", char decorator = '-') const;
  bool noOneHasBusted() const;
  bool noOneHasBlackjack() const;
  void placeBets();
  void printPassState() const;
  void printRoundSummary() const;
  void printGameSummary(int round) const;
  bool playersCanStillDrawCards() const;
  void processOutcome(int chipsInPot) const;
  void processRound(int round);
  void processUserInput();

  bool m_playing;
  int m_currentPot;
  std::shared_ptr<dealer> m_dealer;
  std::shared_ptr<user> m_user;

  const int STARTING_CHIPS = 100;
};


#endif //BURAKU_GAME_H
