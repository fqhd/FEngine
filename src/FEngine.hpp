#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.h"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "ModelRenderer.hpp"
#include "GBuffer.hpp"
#include "DeferredRenderer.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path, Color color);
    void draw();
    void destroy();
    
    Skybox skybox;
    Window window;
    InputManager inputManager;
    Camera camera;
    ModelRenderer modelRenderer;
    DeferredRenderer deferredRenderer;
    std::vector<FObject> objects;
};