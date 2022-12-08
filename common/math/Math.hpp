#ifndef BOX_BREAKER_MATH_H
#define BOX_BREAKER_MATH_H

#include <stdexcept>
#include <utility>
#include <vector>
#include <cmath>
#include <math.h>

namespace BoxBreaker::Common::Math
{
    using Vertices = std::vector<float>;
    using Indices = std::vector<unsigned int>;

    struct Rect
    {
        float x, y, w, h;
    };

    struct Circle
    {
        float x, y, r;
    };

    static std::pair<Vertices, Indices> generateVerticesAndIndices(const Rect &rect)
    {
        return std::make_pair(Vertices{
                rect.x, rect.y, 0.0f,
                rect.x + rect.w, rect.y, 0.0f,
                rect.x + rect.w, rect.y + rect.h, 0.0f,
                rect.x, rect.y + rect.h, 0.0f,
        }, Indices{
                0, 1, 3,
                1, 2, 3
        });
    }

    static std::pair<Vertices, Indices> generateVerticesAndIndices(const Circle &circle)
    {
        constexpr std::size_t pointsCount = 37;

        Vertices vertices(pointsCount * 3);
        Indices indices(pointsCount * 3);

        vertices[0] = circle.x;
        vertices[1] = circle.y;
        vertices[2] = 0.0;

        for(int i = 3; i < vertices.size(); i+=3)
        {
            auto& x = vertices[i];
            auto& y = vertices[i+1];
            auto& z = vertices[i+2];
        }

    }
} // namespace BoxBreaker::Math

#endif //BOX_BREAKER_MATH_H
