//
// Created by bebop on 12/5/22.
//

#ifndef BOX_BREAKER_SHADERPROGRAM_H
#define BOX_BREAKER_SHADERPROGRAM_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>

struct ShaderProgram
{
    ShaderProgram(const char *vertexPath, const char *fragmentPath);

    ShaderProgram();

    void use() const;


private:
    static constexpr const char *defaultVertexPath = "glsl/vertex.vert";
    static constexpr const char *defaultFragmentPath = "glsl/fragment.frag";

    GLuint id;
};


#endif //BOX_BREAKER_SHADERPROGRAM_H
