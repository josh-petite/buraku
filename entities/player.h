//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_PLAYER_H
#define BURAKU_PLAYER_H


#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <iomanip>
#include "card.h"
#include "hand.h"

class player {
public:
  explicit player(std::string name) : player(std::move(name), 0) {}

  player(std::string name, int chips)
    : m_chipTotal(chips),
      m_doublingDown(false),
      m_hand(std::make_shared<hand>()),
      m_maxChipTotal(0),
      m_name(std::move(name)),
      m_standing(false) {}

  virtual std::string getStatus();

  void addToChipTotal(int chips);
  inline bool busted() const { return m_hand->busted(); }
  inline void decreaseChipTotal(int amount) { m_chipTotal -= amount; }
  void resetRound();
  int getChipTotal() const;
  inline int getMaxChipTotal() const { return m_maxChipTotal; }
  inline int getScore() const { return m_hand->getScore(); }
  std::string getName() const;
  inline bool hasBlackjack() const { return m_hand->hasBlackjack(); }
  bool isDoublingDown() const;
  bool standing() const;
  void receiveCard(const card &card);
  void setDoublingDown(bool doublingDown);
  void setStanding(bool standing);
protected:
  std::shared_ptr<hand> m_hand;
private:
  int m_chipTotal;
  int m_maxChipTotal;
  bool m_doublingDown;
  std::string m_name;
  bool m_standing;
};


#endif //BURAKU_PLAYER_H
