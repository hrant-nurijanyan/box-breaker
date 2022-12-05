#include <iostream>

#include "game/BoxBreakerGame.h"


int main()
{
    try
    {
        Game game(std::make_unique<BoxBreakerWindowConfig>());
        game.setInputProcessor(std::make_unique<BoxBreakerInputProcessor>());
        game.loadGameConfig(std::make_unique<BoxBreakerGameConfig>());
        game.loop();
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

}
