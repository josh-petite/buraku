#include <iostream>
#include "entities/game.h"

int main() {

  std::shared_ptr<game> g = std::make_shared<game>();
  g->start();

  return 0;
}