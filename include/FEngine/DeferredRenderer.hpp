#pragma once

#include "GBuffer.hpp"
#include "Shader.hpp"
#include "FObject.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "Skybox.hpp"

class DeferredRenderer {
public:
    void init(Camera* cam, Window* window);
    void draw(FObject* objects, int size);
    void destroy();

    Skybox skybox;
    Shader shader;
    GBuffer gbuffer;
    Camera* camera;
};