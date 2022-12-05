#ifndef BOX_BREAKER_BOXBREAKERGAME_H
#define BOX_BREAKER_BOXBREAKERGAME_H

#include <fstream>
#include <sstream>

#include "Game.h"

struct BoxBreakerWindowConfig : IWindowConfig
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
        if (Game::isKeyPressed(Key::ESC))
        {
            Game::end();
        }
        if (Game::isKeyPressed(Key::RIGHT))
        {
            game.movePlayerRight();
        }

        if (Game::isKeyPressed(Key::LEFT))
        {
            game.movePlayerLeft();
        }
        if (Game::isKeyPressed(Key::SPACE))
        {
            game.start();
        }
    }
};

struct BoxBreakerGameConfig : IGameConfig
{
    Rect getPlayerRect() final
    {
        return {-0.125f, -0.98f, 0.25f, 0.05f};
    }

    Color getPlayerColor() final
    {
        return {1.0f, 0.0f, 0.0f, 1.0f};
    }

    Rect getBallRect() final
    {
        return {-0.00825f, -0.92f, 0.04f, 0.04f};
    }

    Speed getBallInitialSpeed() final
    {
        return {0.0f, 1.0f};
    }

    Color getBallColor() final
    {
        return {0.12f, 1.0f, 1.0f, 1.0f};
    }

    std::vector<Rect> getObstacleRects() final
    {
        return {{0.33, 0.33f, 0.2f, 0.1f}};
    }

    std::vector<Color> getObstacleColors() final
    {
        return {};
    }
};

#endif //BOX_BREAKER_BOXBREAKERGAME_H
