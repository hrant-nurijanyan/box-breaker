#ifndef BOX_BREAKER_DEFAULT_H
#define BOX_BREAKER_DEFAULT_H

#include <GLFW/glfw3.h>

#include "Config.h"

#include "../game/Game.h"

namespace BoxBreaker::Default
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
}

#endif //BOX_BREAKER_DEFAULT_H
