//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_DEALER_H
#define BURAKU_DEALER_H


#include "deck.h"
#include "player.h"

class dealer : public player {
public:
  dealer();
  void reset();
  card drawCard();
private:
  int m_deckIndex;
  std::shared_ptr<deck> m_deck;
};


#endif //BURAKU_DEALER_H
