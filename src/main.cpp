#include <iostream>

#include "reactive/Reactive.h"
#include "config/Default.h"


int main()
{

    BoxBreaker::Config::loadWindowConfig(registry.ctx(),
                                         std::make_unique<BoxBreaker::Default::WindowConfig>());

    BoxBreaker::Game::init(registry.ctx());
    BoxBreaker::Game::loop(registry);
}
