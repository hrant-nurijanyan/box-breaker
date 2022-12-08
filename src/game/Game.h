#ifndef BOX_BREAKER_GAME_H
#define BOX_BREAKER_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#include "../config/Config.h"

#include "../reactive/Reactive.h"

namespace BoxBreaker
{

    struct Game
    {
        Game();

        void run();

    private:
        void movePlayerLeft();
        void movePlayerRight();
        void pause();
        void resume();
        void quit();
        void processInput(GLFWwindow *window);

    private:
        entt::registry registry;
    };
}


#endif //BOX_BREAKER_GAME_H
