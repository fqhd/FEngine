#pragma once
#include <FEngine/CascadeShadowMap.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Skybox.hpp>

namespace FEngine
{
    class MasterRenderer
    {
    public:
        void init(Camera *camera, Window *window);
        void drawObjects(FObject *objects, int size);
        void destroy();

        Skybox skybox;
        Shader shader;
        Camera *camera;
        CascadeShadowMap shadowMap;
    };
}