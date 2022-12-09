#ifndef BOX_BREAKER_DEFAULT_H
#define BOX_BREAKER_DEFAULT_H

#include "Config.h"

#include "../game/Game.h"

namespace BoxBreaker::Config::Default
{

    struct WindowConfig : Config::IWindowConfig
    {
        int getWidth() const final
        {
            return 800;
        }

        int getHeight() const final
        {
            return 600;
        }

        const char *getTitle() const final
        {
            return "Box breaker";
        }

        BoxBreaker::Graphics::Color getColor() const final
        {
            return {0.2f, 0.3f, 0.3f, 1.0f};
        }
    };

    struct GameConfig : Config::IGameConfig
    {
        Math::Rect getPlayerRect() const final
        {
            return {-0.125f, -0.98f, 0.25f, 0.05f};
        }

        Graphics::Color getPlayerColor() const final
        {
            return {1.0f, 0.0f, 0.0f, 1.0f};
        }

        Math::Rect getBallRect() const final
        {
            return {-0.00825f, -0.92f, 0.04f, 0.04f};
        }

        Math::Vector2f getBallInitialSpeed() const final
        {
            return {0.3f, 1.0f};
        }

        Graphics::Color getBallColor() const final
        {
            return {0.12f, 1.0f, 1.0f, 1.0f};
        }

        std::vector<Math::Rect> getObstacleRects() const final
        {
            return {{0.33, 0.33f, 0.2f, 0.1f}};
        }

        std::vector<Graphics::Color> getObstacleColors() const final
        {
            return {};
        }
    };
}

#endif //BOX_BREAKER_DEFAULT_H
