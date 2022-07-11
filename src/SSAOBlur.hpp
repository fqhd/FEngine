#pragma once

#include <GL/glew.h>
#include "Quad.hpp"
#include "Window.hpp"
#include "Shader.hpp"

class SSAOBlur {
public:
    void init(Window* window);
    void draw(GLuint ssaoTexture);
    void destroy();

    Quad quad;
    GLuint fbo;
    GLuint textureID;
    Shader shader;
};