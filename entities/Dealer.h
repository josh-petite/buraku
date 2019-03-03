//
// Created by Josh Petite on 2019-03-03.
//

#ifndef BURAKU_DEALER_H
#define BURAKU_DEALER_H


#include "Deck.h"

class Dealer {
public:
  Dealer();
private:
  std::shared_ptr<Deck> m_deck;
};


#endif //BURAKU_DEALER_H
