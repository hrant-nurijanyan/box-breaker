#ifndef BOX_BREAKER_CONFIG_H
#define BOX_BREAKER_CONFIG_H

#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <memory>

#include "../graphics/Graphics.hpp"
#include "../hash/Hash.h"

namespace BoxBreaker
{
    struct Config
    {
        struct IWindowConfig
        {
            virtual int getWidth() const = 0;

            virtual int getHeight() const = 0;

            virtual const char *getTitle() const = 0;

            virtual Graphics::Color getColor() const = 0;

            virtual ~IWindowConfig() = default;
        };

        static void loadWindowConfig(entt::registry::context &ctx,
                                     const std::unique_ptr<IWindowConfig> &windowConfig);

    };

}

#endif //BOX_BREAKER_CONFIG_H
