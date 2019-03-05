//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_USER_H
#define BURAKU_USER_H


#include "player.h"

class user : public player {
public:
  // referenced via make_shared call in game.cpp
  user(std::string name, int startingChips) : player(std::move(name), startingChips), m_winStreak(0) {}

  std::string getStatus() override;
  inline int getWinstreak() const { return m_winStreak; }
  inline void increaseWinstreak() { m_winStreak++; }
  inline void resetWinstreak() { m_winStreak = 0; }
  void reset() override;
private:
  int m_winStreak;
};


#endif //BURAKU_USER_H
