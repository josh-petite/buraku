//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_DEALER_H
#define BURAKU_DEALER_H


#include "deck.h"
#include "player.h"

class dealer : public player {
public:
  dealer()
    : player("Dealer", 0), m_deck(std::make_shared<deck>()), m_deckIndex(0) {}

  void dealCardTo(player* p);
  void reset() override;
  void takeAction(std::shared_ptr<player> opponent);
private:
  card drawCard();

  std::shared_ptr<deck> m_deck;
  int m_deckIndex;
};


#endif //BURAKU_DEALER_H
