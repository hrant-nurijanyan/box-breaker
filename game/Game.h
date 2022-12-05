#ifndef BOX_BREAKER_GAME_H
#define BOX_BREAKER_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <memory>


#include "../glsl/ShaderProgram.h"
#include "../defines.hpp"

struct Game;

/**
 * @brief Game configuration interface
 */
struct IWindowConfig
{
    virtual int getWidth() = 0;

    virtual int getHeight() = 0;

    virtual const char *getName() = 0;

    virtual Color getBackgroundColor() = 0;

    virtual ~IWindowConfig() = default;
};

struct IInputProcessor
{
    virtual void processInput(Game &game) = 0;

    virtual ~IInputProcessor() = default;
};

struct IGameConfig
{
    virtual Rect getPlayerRect() = 0;

    virtual Color getPlayerColor() = 0;

    virtual Rect getBallRect() = 0;

    virtual Color getBallColor() = 0;

    virtual Speed getBallInitialSpeed() = 0;

    virtual std::vector<Rect> getObstacleRects() = 0;

    virtual std::vector<Color> getObstacleColors() = 0;

    virtual ~IGameConfig() = default;
};


struct Game
{
    using WindowConfigPtr = std::unique_ptr<IWindowConfig>;
    using InputProcessorPtr = std::unique_ptr<IInputProcessor>;
    using GameConfigPtr = std::unique_ptr<IGameConfig>;

    explicit Game(const WindowConfigPtr &windowConfigPtr);

    void setInputProcessor(InputProcessorPtr inputProcessorPtr);

    void loadGameConfig(const GameConfigPtr &gameConfig);

    void start();

    bool gameHasStarted() const;

    void movePlayerRight();

    void movePlayerLeft();

    static void end();

    void loop();

    static bool isKeyPressed(Key key);

    ~Game();

private:
    static constexpr entt::hashed_string KEY_GAME_STARTED = "keyGameStarted";
    static constexpr entt::hashed_string KEY_DELTA_TIME = "keyDeltaTime";
    static constexpr entt::hashed_string KEY_BACKGROUND_COLOR = "keyBackgroundColor";

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

    static constexpr std::array<unsigned int, 6> getRectIndices()
    {
        return {
                0, 1, 3,
                1, 2, 3
        };
    }

    static constexpr std::array<float, 28> getRectVertices(const Rect &rect, const Color &color)
    {
        return {
                rect.x, rect.y, 0.0f, color.r, color.g, color.b, color.a,
                rect.x + rect.width, rect.y, 0.0f, color.r, color.g, color.b, color.a,
                rect.x + rect.width, rect.y + rect.height, 0.0f, color.r, color.g, color.b, color.a,
                rect.x, rect.y + rect.height, 0.0f, color.r, color.g, color.b, color.a
        };
    }

    static constexpr bool rectCollide(const Rect &rect1, const Rect &rect2)
    {
        return rect1.x < rect2.x + rect2.width &&
               rect1.x + rect1.width > rect2.x &&
               rect1.y < rect2.y + rect2.height &&
               rect1.height + rect1.y > rect2.y;
    }

    static void resizeCallback(GLFWwindow *window, int width, int height);


private:
    void updateBallPosition();

    void doCollision();

    static void onRectUpdated(entt::registry &registry, entt::entity entity);

    static void onSpeedUpdated(entt::registry &registry, entt::entity entity);

private:
    entt::registry registry;
    entt::entity player;
    entt::entity ball;
};


#endif //BOX_BREAKER_GAME_H
