#pragma once
#include "CascadeShadowMap.hpp"
#include "FObject.hpp"
#include "Quad.hpp"
#include "FXAA.hpp"
#include "Skybox.hpp"

class MasterRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects(FObject* objects, int size);
    void destroy();

    Skybox skybox;
    FXAA fxaa;
    Shader shader;
    Camera* camera;
    CascadeShadowMap shadowMap;
};