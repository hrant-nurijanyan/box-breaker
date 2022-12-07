#ifndef BOX_BREAKER_ENTT_H
#define BOX_BREAKER_ENTT_H

#include <glad/glad.h>
#include <entt/entt.hpp>
#include <Common.h>

namespace BoxBreaker
{


    struct Functional
    {
        static void onRectCreated(entt::registry &registry, entt::entity entity);

        static void onRectUpdated(entt::registry &registry, entt::entity entity);

        static void onRectDestroyed(entt::registry &registry, entt::entity entity);

        static void onRenderableCreated(entt::registry &registry, entt::entity entity);

        static void onRenderableDestroyed(entt::registry &registry, entt::entity entity);

        static void onRenderDestroyed(entt::registry &registry, entt::entity entity);

        static void onSpeedCreated(entt::registry &registry, entt::entity entity);

        static void onSpeedUpdated(entt::registry &registry, entt::entity entity);

        static void onSpeedDestroyed(entt::registry &registry, entt::entity entity);

    private:
        static void createRender(entt::registry &registry, entt::entity entity, const std::vector<float> &vertices,
                                 const std::vector<unsigned int> &indices);

        static void updateRender(entt::registry &registry, entt::entity entity, const std::vector<float> &vertices,
                                 const std::vector<unsigned int> &indices);

        static std::vector<float> getVertices(const Component::Rect &rect);

        static std::vector<unsigned int> getIndices(const Component::Rect &rect);

        static std::vector<float> getVertices(const Component::Circle &rect);

        static std::vector<unsigned int> getIndices(const Component::Circle &rect);
    };


} // namespace BoxBreaker


#endif //BOX_BREAKER_ENTT_H
