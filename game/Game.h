#ifndef BOX_BREAKER_GAME_H
#define BOX_BREAKER_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>

struct Game;

struct Color
{
    float r, g, b, a;
};

/**
 * @brief Currently supported keys
 */
enum class Key
{
    SPACE,
    ESC,
    UP,
    DOWN,
    RIGHT,
    LEFT
};


/**
 * @brief Game configuration interface
 */
struct IGameConfig
{
    virtual int getWidth() = 0;

    virtual int getHeight() = 0;

    virtual const char *getName() = 0;

    virtual Color getBackgroundColor() = 0;

    virtual ~IGameConfig() = default;
};

struct IInputProcessor
{
    virtual void processInput(Game &game) = 0;

    virtual ~IInputProcessor() = default;
};

struct Game
{
    explicit Game(std::unique_ptr<IGameConfig> gameConfig, std::unique_ptr<IInputProcessor> processor);

    void end();

    void loop();

    bool isKeyPressed(Key key) const;

    ~Game();

private:
    static constexpr int getGlfwKeyFromKey(Key key)
    {
        switch (key)
        {
            case Key::SPACE:
                return GLFW_KEY_SPACE;
            case Key::ESC:
                return GLFW_KEY_ESCAPE;
            case Key::UP:
                return GLFW_KEY_UP;
            case Key::DOWN:
                return GLFW_KEY_DOWN;
            case Key::RIGHT:
                return GLFW_KEY_RIGHT;
            case Key::LEFT:
                return GLFW_KEY_LEFT;
        }
        return -1;
    }

    static void resizeCallback(GLFWwindow* window, int width, int height);
private:
    GLFWwindow *window;
    std::unique_ptr<IGameConfig> config;
    std::unique_ptr<IInputProcessor> processor;
};


#endif //BOX_BREAKER_GAME_H
