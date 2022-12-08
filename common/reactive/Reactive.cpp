#include "Reactive.h"

void BoxBreaker::Common::Reactive::onRectCreated(entt::registry &registry, entt::entity entity)
{
    const auto &rectComponent = registry.get<Component::Rect>(entity);
    bool isDynamic = registry.all_of<Component::Speed>(entity);
    auto vertices = getRectVertices(rectComponent);
    auto indices = getRectIndices(rectComponent);
    registry.emplace<Component::RenderData>(entity, vertices.data(),
                                            vertices.size() * sizeof(float),
                                            indices.data(),
                                            indices.size() * sizeof(unsigned int),
                                            isDynamic);
}

void BoxBreaker::Common::Reactive::onRectUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &rectComponent = registry.get<Component::Rect>(entity);
    auto vertices = getRectVertices(rectComponent);
    auto indices = getRectIndices(rectComponent);
    registry.patch<Component::RenderData>(entity, [&](auto &renderData)
    {
        renderData.verticesData = vertices.data();
        renderData.verticesSize = vertices.size() * sizeof(float);
        renderData.indicesData = indices.data();
        renderData.indicesSize = indices.size() * sizeof(unsigned int);
    });

    if (registry.all_of<Component::RectCollider>(entity))
    {
        registry.patch<Component::RectCollider>(entity, [&](auto &rectCollider)
        {
            rectCollider.rect = rectComponent.rect;
        });
    }
}

void BoxBreaker::Common::Reactive::onRectDestroyed(entt::registry &registry, entt::entity entity)
{
    registry.erase<Component::RenderData>(entity);
}

void BoxBreaker::Common::Reactive::onCircleCreated(entt::registry &registry, entt::entity entity)
{

}

void BoxBreaker::Common::Reactive::onCircleUpdated(entt::registry &registry, entt::entity entity)
{

}

void BoxBreaker::Common::Reactive::onCircleDestroyed(entt::registry &registry, entt::entity entity)
{

}

void BoxBreaker::Common::Reactive::onSpeedCreated(entt::registry &registry, entt::entity entity)
{
    if (registry.all_of<Component::RenderData>(entity))
    {
        registry.patch<Component::RenderData>(entity, [](auto &renderData)
        {
            renderData.isDynamic = true;
        });
    }

}

void BoxBreaker::Common::Reactive::onSpeedUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &speed = registry.get<Component::Speed>(entity);
    auto deltaTime = registry.ctx().get<double>(Hash::KEY_DELTA_TIME);
    if (registry.all_of<BoxBreaker::Common::Component::Rect>(entity))
    {
        registry.patch<BoxBreaker::Common::Component::Rect>(entity, [&](auto &rectComponent)
        {
            rectComponent.rect.x += speed.x * deltaTime;
            rectComponent.rect.y += speed.y * deltaTime;
        });
    }
    if (registry.all_of<BoxBreaker::Common::Component::Circle>(entity))
    {
        registry.patch<BoxBreaker::Common::Component::Circle>(entity, [&](auto &circleComponent)
        {
            circleComponent.circle.x += speed.x * deltaTime;
            circleComponent.circle.y += speed.y * deltaTime;
        });
    }
}

void BoxBreaker::Common::Reactive::onSpeedDestroyed(entt::registry &registry, entt::entity entity)
{
    if (registry.all_of<Component::RenderData>(entity))
    {
        registry.patch<Component::RenderData>(entity, [](auto &renderData)
        {
            renderData.isDynamic = false;
        });
    }
}

void BoxBreaker::Common::Reactive::onRenderDataCreated(entt::registry &registry, entt::entity entity)
{

}

void BoxBreaker::Common::Reactive::onRenderDataUpdated(entt::registry &registry, entt::entity entity)
{

}

void BoxBreaker::Common::Reactive::onRenderDataDestroyed(entt::registry &registry, entt::entity entity)
{

}
