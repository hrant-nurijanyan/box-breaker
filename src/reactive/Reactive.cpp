#include "Reactive.h"

void BoxBreaker::Reactive::onRectCreated(entt::registry &registry, entt::entity entity)
{
    auto render = registry.try_get<Component::Render>(entity);

    // If no render component is attached or attached render is already valid, do nothing
    if (render == nullptr || render->isValid())
    {
        return;
    }

    createRenderComponentData(registry, entity);
}

void BoxBreaker::Reactive::onRectUpdated(entt::registry &registry, entt::entity entity)
{
    if (registry.all_of<Component::Render>(entity))
    {
        registry.patch<Component::Render>(entity); // Trigger patch
    }
}

void BoxBreaker::Reactive::onRectDestroyed(entt::registry &registry, entt::entity entity)
{
    registry.erase<Component::Render>(entity);
}

void BoxBreaker::Reactive::onRenderCreated(entt::registry &registry, entt::entity entity)
{
    auto &render = registry.get<Component::Render>(entity);

    // If already valid render component is created, do nothing
    if (render.isValid())
    {
        return;
    }

    auto rect = registry.try_get<Component::Rect>(entity);
    if (rect == nullptr)
    {
        return;
    }

    createRenderComponentData(registry, entity);
}

void BoxBreaker::Reactive::onRenderUpdated(entt::registry &registry, entt::entity entity)
{
    if (!registry.all_of<Component::Rect>(entity))
    {
        return;
    }

    auto [render, rect] = registry.get<Component::Render, Component::Rect>(entity);


    auto vertices = Math::getVertices(rect);
    auto indices = Math::getIndices(rect);

    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}


void BoxBreaker::Reactive::onRenderDestroyed(entt::registry &registry, entt::entity entity)
{
    auto &render = registry.get<Component::Render>(entity);

    glDeleteVertexArrays(1, &render.VAO);
    glDeleteBuffers(1, &render.VBO);
    glDeleteBuffers(1, &render.EBO);

}

void BoxBreaker::Reactive::onSpeedCreated(entt::registry &registry, entt::entity entity)
{
    if (registry.all_of<Component::Rect, Component::Render>(entity))
    {
        registry.patch<Component::Render>(entity, [](auto &render)
        {
            render.isDynamic = true;
        });
    }
}

void BoxBreaker::Reactive::onSpeedUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &speed = registry.get<Component::Speed>(entity);
    if (registry.all_of<Component::Rect>(entity))
    {

        registry.patch<Component::Rect>(entity, [&](auto &rect)
        {
            auto deltaTime = registry.ctx().get<double>(Hash::KEY_DELTA_TIME);
            rect.x += speed.x * deltaTime;
            rect.y += speed.y * deltaTime;
        });
    }
}

void BoxBreaker::Reactive::onSpeedDestroyed(entt::registry &registry, entt::entity entity)
{
    if (registry.all_of<Component::Rect, Component::Render>(entity))
    {
        registry.patch<Component::Render>(entity, [](auto &render)
        {
            render.isDynamic = false;
        });
    }
}

void BoxBreaker::Reactive::createRenderComponentData(entt::registry &registry, entt::entity entity)
{
    if (!registry.all_of<Component::Render, Component::Rect>(entity))
    {
        return;
    }

    auto [render, rect] = registry.get<Component::Render, Component::Rect>(entity);

    render.isDynamic = registry.all_of<Component::Speed>(entity);

    glGenVertexArrays(1, &render.VAO);
    glGenBuffers(1, &render.VBO);
    glGenBuffers(1, &render.EBO);

    auto vertices = Math::getVertices(rect);
    auto indices = Math::getIndices(rect);

    glBindVertexArray(render.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


