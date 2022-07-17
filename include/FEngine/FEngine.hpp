#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "MasterRenderer.hpp"
#include "GBuffer.hpp"
#include "DeferredRenderer.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path, Color color);
    void draw();
    void destroy();
    
    Window window;
    InputManager inputManager;
    Camera camera;
    MasterRenderer masterRenderer;
    DeferredRenderer deferredRenderer;
    std::vector<FObject> objects;
};