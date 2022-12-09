#ifndef BOX_BREAKER_CONFIG_H
#define BOX_BREAKER_CONFIG_H

#include <entt/entt.hpp>
#include <memory>
#include "../math/Math.hpp"

#include "../graphics/Graphics.hpp"
#include "../hash/Hash.h"

namespace BoxBreaker::Config
{
    struct IWindowConfig
    {
        virtual int getWidth() const = 0;

        virtual int getHeight() const = 0;

        virtual const char *getTitle() const = 0;

        virtual Graphics::Color getColor() const = 0;

        virtual ~IWindowConfig() = default;
    };

    struct IGameConfig
    {
        virtual Math::Rect getPlayerRect() const = 0;

        virtual Graphics::Color getPlayerColor() const = 0;

        virtual Math::Rect getBallRect() const = 0;

        virtual Graphics::Color getBallColor() const = 0;

        virtual Math::Vector2f getBallInitialSpeed() const = 0;

        virtual std::vector<Math::Rect> getObstacleRects() const = 0;

        virtual std::vector<Graphics::Color> getObstacleColors() const = 0;

        virtual ~IGameConfig() = default;
    };


}

#endif //BOX_BREAKER_CONFIG_H
