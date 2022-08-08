#pragma once
#include <FEngine/CascadeShadowMap.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Quad.hpp>
#include <FEngine/FXAA.hpp>
#include <FEngine/Skybox.hpp>

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