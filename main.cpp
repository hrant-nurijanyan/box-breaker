#include <iostream>

#include "game/BoxBreakerGame.h"


int main()
{
    Game game(std::make_unique<BoxBreakerConfig>(), std::make_unique<BoxBreakerInputProcessor>());
    game.loop();
}
