#ifndef BOX_BREAKER_REACTIVE_H
#define BOX_BREAKER_REACTIVE_H

#include <glad/glad.h>
#include <entt/entt.hpp>
#include "../component/Component.h"
#include "../hash/Hash.h"

namespace BoxBreaker::Common
{
    struct Reactive
    {
        static void onRectCreated(entt::registry &registry, entt::entity entity);

        static void onRectUpdated(entt::registry &registry, entt::entity entity);

        static void onRectDestroyed(entt::registry &registry, entt::entity entity);

        static void onCircleCreated(entt::registry &registry, entt::entity entity);

        static void onCircleUpdated(entt::registry &registry, entt::entity entity);

        static void onCircleDestroyed(entt::registry &registry, entt::entity entity);

        static void onSpeedCreated(entt::registry &registry, entt::entity entity);

        static void onSpeedUpdated(entt::registry &registry, entt::entity entity);

        static void onSpeedDestroyed(entt::registry &registry, entt::entity entity);

        static void onRenderDataCreated(entt::registry &registry, entt::entity entity);

        static void onRenderDataUpdated(entt::registry &registry, entt::entity entity);

        static void onRenderDataDestroyed(entt::registry &registry, entt::entity entity);

    private:
        static std::vector<float> getVertices(const Component::Rect &rectComponent)
        {
            const auto &rect = rectComponent.rect;
            const auto &color = rectComponent.color;
            return {
                    rect.x, rect.y, 0.0f,
                    color.r, color.g, color.b, color.a,
                    rect.x + rect.w, rect.y, 0.0f,
                    color.r, color.g, color.b, color.a,
                    rect.x + rect.w, rect.y + rect.h, 0.0f,
                    color.r, color.g, color.b, color.a,
                    rect.x, rect.y + rect.h, 0.0f,
                    color.r, color.g, color.b, color.a,
            };
        }

        static std::vector<unsigned int> getIndices(const Component::Rect &rectComponent)
        {
            return {
                    0, 1, 3,
                    1, 2, 3
            };
        }

        static std::vector<float> getVertices(const Component::Circle &circleComponent)
        {

        }

        static std::vector<unsigned int> getIndices(const Component::Circle &circleComponent)
        {

        }
    };
}


#endif //BOX_BREAKER_REACTIVE_H
