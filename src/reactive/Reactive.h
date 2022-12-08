#ifndef BOX_BREAKER_REACTIVE_H
#define BOX_BREAKER_REACTIVE_H

#include "glad/glad.h"
#include "entt/entt.hpp"
#include "../component/Component.hpp"
#include "../hash/Hash.h"

namespace BoxBreaker
{
    struct Reactive
    {

        static void onRectCreated(entt::registry &registry, entt::entity entity);

        static void onRectUpdated(entt::registry &registry, entt::entity entity);

        static void onRectDestroyed(entt::registry &registry, entt::entity entity);

        static void onRenderCreated(entt::registry &registry, entt::entity entity);

        static void onRenderUpdated(entt::registry &registry, entt::entity entity);

        static void onRenderDestroyed(entt::registry &registry, entt::entity entity);

        static void onSpeedCreated(entt::registry &registry, entt::entity entity);

        static void onSpeedUpdated(entt::registry &registry, entt::entity entity);

        static void onSpeedDestroyed(entt::registry &registry, entt::entity entity);

    private:
        static void createRenderComponentData(entt::registry &registry, entt::entity entity);

    };
}


#endif //BOX_BREAKER_REACTIVE_H
