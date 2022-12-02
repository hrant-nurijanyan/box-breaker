#ifndef BOX_BREAKER_BOXBREAKERGAME_H
#define BOX_BREAKER_BOXBREAKERGAME_H

#include "Game.h"

struct BoxBreakerConfig : IGameConfig
{
    int getWidth() final
    {
        return 800;
    }

    int getHeight() final
    {
        return 600;
    }

    const char *getName() final
    {
        return "Box breaker";
    }

    Color getBackgroundColor() final
    {
        return {0.2f, 0.3f, 0.3f, 1.0f};
    }
};

struct BoxBreakerInputProcessor : IInputProcessor
{
    void processInput(Game &game) final
    {
        if (game.isKeyPressed(Key::ESC))
        {
            game.end();
        }
    }
};

#endif //BOX_BREAKER_BOXBREAKERGAME_H
