#include "Game.h"

BoxBreaker::Game::Game()
{
    registry.on_construct<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectCreated>();
    registry.on_update<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectUpdated>();
    registry.on_destroy<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectDestroyed>();
    registry.on_construct<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderCreated>();
    registry.on_update<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderUpdated>();
    registry.on_destroy<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderDestroyed>();
    registry.on_construct<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedCreated>();
    registry.on_update<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedUpdated>();
    registry.on_destroy<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedDestroyed>();
}

void BoxBreaker::Game::run()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    const auto &ctx = registry.ctx();

    auto window = glfwCreateWindow(ctx.get<int>(Hash::KEY_WINDOW_WIDTH),
                                   ctx.get<int>(Hash::KEY_WINDOW_HEIGHT),
                                   ctx.get<const char *>(Hash::KEY_WINDOW_TITLE),
                                   nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Cannot create window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Cannot load glad");
    }
}

void BoxBreaker::Game::processInput(GLFWwindow *window)
{
    if (window == nullptr)
    {
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        movePlayerLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        movePlayerRight();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        auto paused = registry.ctx().get<bool>(Hash::KEY_GAME_IS_PAUSED);
        if (paused)
        {
            resume();
        } else
        {
            pause();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        quit();
    }
}
