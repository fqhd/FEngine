#pragma once

#include "GBuffer.hpp"
#include "Shader.hpp"
#include "FObject.h"
#include "Camera.hpp"

class DeferredRenderer {
public:
    void init(Camera* cam);
    void draw(FObject* objects, int size);
    void destroy();

    Shader shader;
    GBuffer gbuffer;
    Camera* camera;
};