#pragma once
#include "CascadeShadowMap.hpp"
#include "FObject.h"

class ModelRenderer {
public:
    void init(Camera* camera, Window* window);
    void drawObjects(FObject* objects, int size);
    void destroy();
    Shader shader;
    Camera* camera;
    CascadeShadowMap shadowMap;
};