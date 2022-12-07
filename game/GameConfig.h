#ifndef BOX_BREAKER_GAMECONFIG_H
#define BOX_BREAKER_GAMECONFIG_H

#include <Common.h>

namespace BoxBreaker::Game
{
    struct GameConfig
    {
        static int getWindowWidth(const entt::registry::context &ctx);

        static int getWindowHeight(const entt::registry::context &ctx);

        static const char *getWindowTitle(const entt::registry::context &ctx);

        static Common::Component::Color getWindowBackgroundColor(const entt::registry::context &ctx);

        static Common::Component::Rect getPlayerRect(const entt::registry::context &ctx);

        static Common::Component::Color getPlayerColor(const entt::registry::context &ctx);

        static Common::Component::Rect getBallRect(const entt::registry::context &ctx);

        static Common::Component::Color getBallColor(const entt::registry::context &ctx);

        static std::vector<Common::Component::Rect> getObstacleRects(const entt::registry::context &ctx);

        static std::vector<Common::Component::Color> getObstacleColors(const entt::registry::context &ctx);

    private:
        template<typename T>
        static T getOrDefault(const entt::registry::context &ctx, const entt::hashed_string &name, T def)
        {
            auto ptr = ctx.find<T>(name);
            return ptr != nullptr ? *ptr : def;
        }
    };
}


#endif //BOX_BREAKER_GAMECONFIG_H
