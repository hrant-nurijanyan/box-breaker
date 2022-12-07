#include "GameConfig.h"

int BoxBreaker::Game::GameConfig::getWindowWidth(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_WINDOW_WIDTH, 800);
}

int BoxBreaker::Game::GameConfig::getWindowHeight(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_WINDOW_HEIGHT, 600);
}

const char *BoxBreaker::Game::GameConfig::getWindowTitle(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_WINDOW_TITLE, "BoxBreaker");
}

BoxBreaker::Common::Component::Color
BoxBreaker::Game::GameConfig::getWindowBackgroundColor(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_WINDOW_BACKGROUND_COLOR, Common::Component::Color::black());
}

BoxBreaker::Common::Component::Rect
BoxBreaker::Game::GameConfig::getPlayerRect(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_PLAYER_RECT, Common::Component::Rect{});
}

BoxBreaker::Common::Component::Color
BoxBreaker::Game::GameConfig::getPlayerColor(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_PLAYER_COLOR, Common::Component::Color::green());
}

BoxBreaker::Common::Component::Rect BoxBreaker::Game::GameConfig::getBallRect(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_BALL_RECT, Common::Component::Rect{});
}

BoxBreaker::Common::Component::Color
BoxBreaker::Game::GameConfig::getBallColor(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_BALL_COLOR, Common::Component::Color::blue());
}

std::vector<BoxBreaker::Common::Component::Rect>
BoxBreaker::Game::GameConfig::getObstacleRects(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_OBSTACLE_RECTS, std::vector<Common::Component::Rect>{});
}

std::vector<BoxBreaker::Common::Component::Color>
BoxBreaker::Game::GameConfig::getObstacleColors(const entt::registry::context &ctx)
{
    return getOrDefault(ctx, Common::Hash::KEY_OBSTACLE_COLORS, std::vector<Common::Component::Color>{});
}
