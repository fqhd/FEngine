#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "MasterRenderer.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    void draw();
    void destroy();
    
    Window window;
    InputManager inputManager;
    Camera camera;
    MasterRenderer masterRenderer;
};