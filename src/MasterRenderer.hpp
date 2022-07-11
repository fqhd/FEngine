#pragma once
#include "CascadeShadowMap.hpp"
#include "FObject.h"
#include "Quad.hpp"
#include "DeferredRenderer.hpp"
#include "SSAO.hpp"

class MasterRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects(FObject* objects, int size, DeferredRenderer& renderer);
    void destroy();
    SSAO ssao;
    Quad quad;
    Shader shader;
    Camera* camera;
    CascadeShadowMap shadowMap;
};