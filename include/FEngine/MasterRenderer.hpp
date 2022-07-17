#pragma once
#include "CascadeShadowMap.hpp"
#include "FObject.hpp"
#include "Quad.hpp"
#include "DeferredRenderer.hpp"
#include "SSAO.hpp"
#include "SSAOBlur.hpp"
#include "FXAA.hpp"

class MasterRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects(FObject* objects, int size, DeferredRenderer& renderer);
    void destroy();
    FXAA fxaa;
    SSAO ssao;
    Quad quad;
    Shader shader;
    Camera* camera;
    SSAOBlur ssaoBlur;
    CascadeShadowMap shadowMap;
};