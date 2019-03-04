//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_PLAYER_H
#define BURAKU_PLAYER_H


#include <string>
#include <utility>
#include <vector>
#include "card.h"

class player {
public:
  player(std::string name, int chips)
    : m_chipTotal(chips), m_currentBet(0), m_doublingDown(false), m_standing(false), m_name(std::move(name)) {}

  virtual void reset() = 0;

  void addToChipTotal(int chips);
  int calculateScoreWithAces(int score, int numberOfAces) const;
  void discardHand();
  int getChipTotal() const;
  int getCurrentBet() const;
  int getCurrentHandScore() const;
  std::vector<card> getHand() const;
  std::string getName() const;
  bool hasBlackjack() const;
  bool busted() const;
  bool isDoublingDown() const;
  bool standing() const;
  void receiveCard(const card &card);
  void setCurrentBet(int bet);
  void setDoublingDown(bool doublingDown);
  void setStanding(bool standing);
private:
  int m_chipTotal;
  int m_currentBet;
  bool m_doublingDown;
  std::vector<card> m_hand;
  std::string m_name;
  bool m_standing;
};

std::ostream& operator<<(std::ostream& stream, const player* p);


#endif //BURAKU_PLAYER_H
