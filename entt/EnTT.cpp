#include "EnTT.h"

void BoxBreaker::Functional::onRectCreated(entt::registry &registry, entt::entity entity)
{
    const auto &rect = registry.get<Common::Component::Rect>(entity);

    if (rect.w < 0 || rect.h < 0)
    {
        throw std::runtime_error("Invalid rect dimensions");
    }

    // If no renderable component no need to generate render vertices and indices
    if (!registry.all_of<Common::Component::Renderable>(entity))
    {
        return;
    }

    createRender(registry, entity, getVertices(rect), getIndices(rect));
}

void BoxBreaker::Functional::onRectUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &rect = registry.get<Common::Component::Rect>(entity);

    if (rect.w < 0 || rect.h < 0)
    {
        throw std::runtime_error("Invalid rect dimensions");
    }

    if (!registry.all_of<Common::Component::Renderable>(entity))
    {
        return;
    }
    updateRender(registry, entity, getVertices(rect), getIndices(rect));
}

void BoxBreaker::Functional::onRectDestroyed(entt::registry &registry, entt::entity entity)
{
    registry.erase<Common::Component::Render>(entity);
}

void BoxBreaker::Functional::onRenderableCreated(entt::registry &registry, entt::entity entity)
{
    auto rectPtr = registry.try_get<Common::Component::Rect>(entity);
    if (rectPtr)
    {
        createRender(registry, entity, getVertices(*rectPtr), getIndices(*rectPtr));
        return;
    }

    auto circlePtr = registry.try_get<Common::Component::Circle>(entity);
    if (circlePtr)
    {
        createRender(registry, entity, getVertices(*circlePtr), getIndices(*circlePtr));
        return;
    }
}

void BoxBreaker::Functional::onRenderableDestroyed(entt::registry &registry, entt::entity entity)
{
    registry.erase<Common::Component::Render>(entity);
}

void BoxBreaker::Functional::onSpeedCreated(entt::registry &registry, entt::entity entity)
{
    if (!registry.any_of<Common::Component::Rect, Common::Component::Circle>(entity))
    {
        return;
    }

    if (!registry.all_of<Common::Component::Renderable>(entity))
    {
        return;
    }

    auto &render = registry.get<Common::Component::Render>(entity);


    int bufferSize = 0;
    glGetNamedBufferParameteriv(render.VBO, GL_BUFFER_SIZE, &bufferSize);
    if (bufferSize == 0)
    {
        return;
    }

    std::vector<float> vertices;
    glGetNamedBufferSubData(render.VBO, 0, bufferSize, vertices.data());
    glGetNamedBufferParameteriv(render.EBO, GL_BUFFER_SIZE, &bufferSize);
    if (bufferSize == 0)
    {
        return;
    }

    std::vector<unsigned int> indices;
    glGetNamedBufferSubData(render.EBO, 0, bufferSize, indices.data());

    updateRender(registry, entity, vertices, indices);
}

void BoxBreaker::Functional::onSpeedUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &speed = registry.get<Common::Component::Speed>(entity);
    registry.patch<Common::Component::Rect>(entity, [&](auto &rect)
    {
        rect.x += speed.x * registry.ctx().get<double>(Common::Hash::KEY_DELTA_TIME);
        rect.y += speed.y * registry.ctx().get<double>(Common::Hash::KEY_DELTA_TIME);
    });
}

void BoxBreaker::Functional::onSpeedDestroyed(entt::registry &registry, entt::entity entity)
{
    if (!registry.any_of<Common::Component::Rect, Common::Component::Circle>(entity))
    {
        return;
    }

    if (!registry.all_of<Common::Component::Renderable>(entity))
    {
        return;
    }

    auto &render = registry.get<Common::Component::Render>(entity);


    int bufferSize = 0;
    glGetNamedBufferParameteriv(render.VBO, GL_BUFFER_SIZE, &bufferSize);
    if (bufferSize == 0)
    {
        return;
    }

    std::vector<float> vertices(bufferSize / sizeof(float));
    glGetNamedBufferSubData(render.VBO, 0, bufferSize, vertices.data());
    glGetNamedBufferParameteriv(render.EBO, GL_BUFFER_SIZE, &bufferSize);
    if (bufferSize == 0)
    {
        return;
    }

    std::vector<unsigned int> indices(bufferSize / sizeof(unsigned int));
    glGetNamedBufferSubData(render.EBO, 0, bufferSize, indices.data());

    updateRender(registry, entity, vertices, indices);
}

void BoxBreaker::Functional::onRenderDestroyed(entt::registry &registry, entt::entity entity)
{
    auto &render = registry.get<Common::Component::Render>(entity);
    glDeleteVertexArrays(1, &render.VAO);
    glDeleteBuffers(1, &render.VBO);
    glDeleteBuffers(1, &render.EBO);
}

void
BoxBreaker::Functional::createRender(entt::registry &registry, entt::entity entity, const std::vector<float> &vertices,
                                     const std::vector<unsigned int> &indices)
{
    unsigned int VAO, VBO, EBO;

    bool isDynamic = registry.all_of<Common::Component::Speed>(entity);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                 isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(),
                 isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindVertexArray(0);

    registry.emplace<Common::Component::Render>(entity, VAO, VBO, EBO);
}

void
BoxBreaker::Functional::updateRender(entt::registry &registry, entt::entity entity, const std::vector<float> &vertices,
                                     const std::vector<unsigned int> &indices)
{
    registry.patch<Common::Component::Render>(entity, [&](auto &render)
    {
        bool isDynamic = registry.all_of<Common::Component::Speed>(entity);
        glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);
        glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), vertices.data(),
                     isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    });
}

std::vector<float> BoxBreaker::Functional::getVertices(const BoxBreaker::Common::Component::Rect &rect)
{
    return {
            rect.x, rect.y, 0.0f,
            rect.x + rect.w, rect.y, 0.0f,
            rect.x + rect.w, rect.y + rect.h, 0.0f,
            rect.x, rect.y + rect.h, 0.0f,
    };
}

std::vector<unsigned int> BoxBreaker::Functional::getIndices(const BoxBreaker::Common::Component::Rect &rect)
{
    return {
            0, 1, 3,
            1, 2, 3
    };
}

std::vector<float> BoxBreaker::Functional::getVertices(const BoxBreaker::Common::Component::Circle &rect)
{
    return {};
}

std::vector<unsigned int> BoxBreaker::Functional::getIndices(const BoxBreaker::Common::Component::Circle &rect)
{
    return {};
}


