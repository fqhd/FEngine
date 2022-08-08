#pragma once

#include "glad.h"
#include <FEngine/Shader.hpp>
#include <FEngine/Quad.hpp>
#include <FEngine/Window.hpp>

class FXAA {
public:
    void init(Window* window);
    void bind();
    void unbind();
    void drawWithFXAA();
    void destroy();

private:
    GLuint fbo;
    GLuint rbo;
    GLuint textureID;
    Shader shader;
    Quad quad;
    Window* window;
};