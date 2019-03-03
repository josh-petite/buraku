#include <iostream>
#include "entities/Game.h"

int main() {

  std::shared_ptr<Player> p = std::make_shared<Player>("Josh");
  Game game(p);



  return 0;
}