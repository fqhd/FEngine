#pragma once
#include "CascadeShadowMap.hpp"
#include "FObject.hpp"
#include "Quad.hpp"
#include "DeferredRenderer.hpp"
#include "FXAA.hpp"

class MasterRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects(FObject* objects, int size, DeferredRenderer& renderer);
    void destroy();
    FXAA fxaa;
    Quad quad;
    Shader shader;
    Camera* camera;
    CascadeShadowMap shadowMap;
};