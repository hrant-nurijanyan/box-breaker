#include <iostream>
#include "config/Default.h"
#include "game/Game.h"


int main()
{
    try
    {
        BoxBreaker::Game game;
        game.loadWindowConfig(std::make_unique<BoxBreaker::Config::Default::WindowConfig>());
        game.loadGameConfig(std::make_unique<BoxBreaker::Config::Default::GameConfig>());
        game.run();
    } catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
