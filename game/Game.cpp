#include "Game.h"

Game::Game(std::unique_ptr<IGameConfig> gameConfig, std::unique_ptr<IInputProcessor> inputProcessor) : config(
        std::move(gameConfig)), processor(std::move(inputProcessor))
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(config->getWidth(), config->getHeight(), config->getName(), nullptr,
                              nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Cannot create glfw window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Cannot initialize glad");
    }

    glViewport(0, 0, config->getWidth(), config->getHeight());

    glfwSetFramebufferSizeCallback(window, resizeCallback);
}

Game::~Game()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::end()
{
    glfwSetWindowShouldClose(window, true);
}

bool Game::isKeyPressed(Key key) const
{
    auto glfwKey = getGlfwKeyFromKey(key);
    return glfwGetKey(window, glfwKey) == GLFW_PRESS;
}

void Game::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        processor->processInput(*this);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
