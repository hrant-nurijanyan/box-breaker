#ifndef BOX_BREAKER_GAME_H
#define BOX_BREAKER_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <Common.h>


#include "../glsl/ShaderProgram.h"
#include "../entt/EnTT.h"

namespace BoxBreaker
{
    struct IWindowConfig
    {
        virtual int getWidth() const = 0;

        virtual int getHeight() const = 0;

        virtual const char *getTitle() const = 0;

        virtual Common::Component::Color getBackgroundColor() = 0;

        virtual ~IWindowConfig() = default;
    };

    struct IGameConfig
    {
        virtual Common::Component::Rect getPlayerRect() const = 0;

        virtual Common::Component::Color getPlayerColor() const = 0;

        virtual Common::Component::Rect getBallRect() const = 0;

        virtual Common::Component::Color getBallColor() const = 0;


        virtual Common::Component::Speed getBallInitialSpeed() const = 0;

        virtual std::vector<Common::Component::Rect> getObstacleRects() const = 0;

        virtual std::vector<Common::Component::Color> getObstacleColors() const = 0;

        virtual ~IGameConfig() = default;
    };

    struct IInputProcessor
    {
        enum class Key
        {
            SPACE,
            ESC,
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        virtual void processInput() = 0;

        bool isKeyPressed(Key key) const;

        virtual ~IInputProcessor() = default;

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
    };


}

struct Game
{

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


private:
    entt::registry registry;
};


#endif //BOX_BREAKER_GAME_H
