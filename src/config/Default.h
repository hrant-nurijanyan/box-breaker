#ifndef BOX_BREAKER_DEFAULT_H
#define BOX_BREAKER_DEFAULT_H

#include <GLFW/glfw3.h>

#include "Config.h"

namespace BoxBreaker::Default
{
    struct GLConfig : Config::IGLConfig
    {
        int getVersionMajor() final
        {
            return 3;
        }

        int getVersionMinor() final
        {
            return 3;
        }

        int getProfile() final
        {
            return GLFW_OPENGL_CORE_PROFILE;
        }
    };

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
