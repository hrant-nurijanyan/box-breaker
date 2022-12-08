#ifndef BOX_BREAKER_MATH_HPP
#define BOX_BREAKER_MATH_HPP

#include <iostream>
#include <stdexcept>
#include <utility>
#include <array>
#include <cmath>

namespace BoxBreaker::Math
{
    struct Rect
    {
        float x, y, w, h;
    };

    static constexpr std::array<float, 12> getVertices(const Rect &rect)
    {
        return {
                rect.x, rect.y, 0.0f,
                rect.x + rect.w, rect.y, 0.0f,
                rect.x + rect.w, rect.y + rect.h, 0.0f,
                rect.x, rect.y + rect.h, 0.0f,
        };
    }

    static constexpr std::array<unsigned int, 6> getIndices(const Rect &rect)
    {
        return {
                0, 1, 3,
                1, 2, 3
        };
    }
} // namespace BoxBreaker::Math

#endif //BOX_BREAKER_MATH_HPP
