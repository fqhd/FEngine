#pragma once

#include "glad.h"
#include "Shader.hpp"
#include "Quad.hpp"
#include "Window.hpp"

class FXAA {
public:
    void init(Window* window);
    void bind();
    void unbind();
    void drawWithFXAA();
    void destroy();

private:
    GLuint fbo;
    GLuint textureID;
    Shader shader;
    Quad quad;
    Window* window;
};