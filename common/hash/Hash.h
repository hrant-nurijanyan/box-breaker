#ifndef BOX_BREAKER_HASH_H
#define BOX_BREAKER_HASH_H

#include <entt/entt.hpp>

using namespace entt::literals;

namespace BoxBreaker::Common::Hash
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

#endif //BOX_BREAKER_HASH_H
