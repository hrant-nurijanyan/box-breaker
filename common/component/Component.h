#ifndef BOX_BREAKER_COMPONENT_H
#define BOX_BREAKER_COMPONENT_H

#include "../math/Math.hpp"
#include "../graphics/Graphics.h"

namespace BoxBreaker::Common::Component
{
    struct Player
    {
    };

    struct Ball
    {

    };
    struct Box
    {

    };

    struct RectCollider
    {
        Math::Rect rect;
    };

    struct CircleCollider
    {
        Math::Circle circle;
    };

    struct Rect
    {
        Math::Rect rect;
        Graphics::Color color;
    };

    struct Circle
    {
        Math::Circle circle;
        Graphics::Color color;
    };

    struct Speed
    {
        float x, y;
    };

    struct RenderData
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        bool isDynamic;
    };

    struct Render
    {
        unsigned int VAO, VBO, EBO;
    };


}

#endif //BOX_BREAKER_COMPONENT_H
