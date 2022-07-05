#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.h"
#include "Shader.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path);
    void draw(const FObject* objects, int numEntities);
    
    Shader shader;
    Window window;
    InputManager inputManager;
    Camera camera;
};