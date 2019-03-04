//
// Created by Josh Petite on 2019-03-03.
//

#include "user.h"

void user::reset() {
  discardHand();
  setDoublingDown(false);
  setStanding(false);
}