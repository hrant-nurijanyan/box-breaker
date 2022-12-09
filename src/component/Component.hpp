#ifndef BOX_BREAKER_COMPONENT_HPP
#define BOX_BREAKER_COMPONENT_HPP

#include "../math/Math.hpp"
#include "../graphics/Graphics.hpp"

namespace BoxBreaker::Component {
    // Struct tag for walls
    struct Wall {
    };
    using Speed = Math::Vector2f;
    using Rect = Math::Rect;
    using Color = Graphics::Color;

    struct Render {
        unsigned int VAO, VBO, EBO;
        bool isDynamic;

        constexpr bool isValid() const {
            return VAO != 0 && VBO != 0 && EBO != 0;
        }
    };

}

#endif //BOX_BREAKER_COMPONENT_HPP
