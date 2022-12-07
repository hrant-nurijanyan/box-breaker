#ifndef BOX_BREAKER_COMMON_H
#define BOX_BREAKER_COMMON_H

#include <entt/entt.hpp>

using namespace entt::literals;

namespace BoxBreaker::Common
{
    namespace Hash
    {
        static constexpr auto KEY_DELTA_TIME = "keyDeltaTime"_hs;
        static constexpr auto KEY_WINDOW_WIDTH = "keyWindowWidth"_hs;
        static constexpr auto KEY_WINDOW_HEIGHT = "keyWindowHeight"_hs;
        static constexpr auto KEY_WINDOW_TITLE = "keyWindowTitle"_hs;
        static constexpr auto KEY_WINDOW_BACKGROUND_COLOR = "keyWindowBackgroundColor"_hs;

        static constexpr auto KEY_PLAYER_RECT = "keyPlayerRect"_hs;
        static constexpr auto KEY_PLAYER_COLOR = "keyPlayerColor"_hs;
        static constexpr auto KEY_BALL_RECT = "keyBallRect"_hs;
        static constexpr auto KEY_BALL_COLOR = "keyBallColor"_hs;
        static constexpr auto KEY_BALL_INITIAL_SPEED = "keyBallInitialSpeed"_hs;
        static constexpr auto KEY_OBSTACLE_RECTS = "keyObstacleRects"_hs;
        static constexpr auto KEY_OBSTACLE_COLORS = "keyObstacleColors"_hs;
    }


    namespace Component
    {
        struct Renderable
        {

        };

        struct Player
        {
        };

        struct Ball
        {
        };

        struct Obstacle
        {
        };

        struct Color
        {
            float r, g, b, a;

            static constexpr Color white()
            {
                return {1.0f, 1.0f, 1.0f, 1.0f};
            }

            static constexpr Color black()
            {
                return {0.0f, 0.0f, 0.0f, 1.0f};
            }

            static constexpr Color red()
            {
                return {1.0f, 0.0f, 0.0f, 1.0f};
            }

            static constexpr Color green()
            {
                return {0.0f, 1.0f, 0.0f, 1.0f};
            }

            static constexpr Color blue()
            {
                return {0.0f, 0.0f, 1.0f, 0.0f};
            }
        };

        struct Position
        {
            float posX, posY;
        };

        struct Rect
        {
            Rect() : x(0), y(0), w(0), h(0)
            {
            }

            float x, y, w, h;
        };

        struct Circle
        {
            float x, y, r;
        };

        struct Speed
        {
            float x, y;
        };

        struct Render
        {
            unsigned int VAO, VBO, EBO;
        };
    }
}

#endif //BOX_BREAKER_COMMON_H
