#pragma once

#include "Shader.hpp"
#include "Window.hpp"
#include "Quad.hpp"
#include "DeferredRenderer.hpp"
#include "SSAOTexture.hpp"
#include "Camera.hpp"

class SSAO
{
public:
    void init(Window *window);
    void draw(DeferredRenderer &renderer, Camera *camera);
    void destroy();

    std::vector<glm::vec3> ssaoKernel;
    GLuint fbo;
    GLuint textureID;
    Shader shader;
    Quad quad;
    SSAOTexture noiseTexture;
    Window *window;
};