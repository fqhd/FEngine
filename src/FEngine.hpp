#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.h"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "CascadeShadowMap.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path, Color color);
    void draw();
    void destroy();
    glm::mat4 getLightSpaceMatrix(const float nearPlane, const float farPlane);
    
    Skybox skybox;
    Shader shader;
    Window window;
    InputManager inputManager;
    CascadeShadowMap shadowMap;
    Camera camera;
    std::vector<FObject> objects;
};