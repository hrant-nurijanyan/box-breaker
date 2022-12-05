#ifndef BOX_BREAKER_DEFINES_HPP
#define BOX_BREAKER_DEFINES_HPP

#include <glad/glad.h>

enum class Key
{
    SPACE,
    ESC,
    UP,
    DOWN,
    RIGHT,
    LEFT
};

struct Color
{
    float r, g, b, a;
};

struct Speed
{
    float x, y;
};

struct Rect
{
    float x, y, width, height;
};

struct Render
{
    GLuint VAO;
    GLuint VBO;
};


#endif // BOX_BREAKER_DEFINES_HPP