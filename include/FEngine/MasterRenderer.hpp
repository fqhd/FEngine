#pragma once
#include "CascadeShadowMap.hpp"
#include "FXAA.hpp"
#include "Skybox.hpp"
#include "InstanceRenderer.hpp"

class MasterRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects();
    void destroy();

    InstanceRenderer instanceRenderer;
    Skybox skybox;
    FXAA fxaa;
    Shader shader;
    Camera* camera;
    CascadeShadowMap shadowMap;
};