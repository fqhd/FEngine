#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.hpp"
#include "Shader.hpp"
#include "TextureManager.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path);
    void draw();
    void destroy();
    
    Shader shader;
    Window window;
    InputManager inputManager;
    Camera camera;
    TextureManager textureManager;
    std::vector<FObject> objects;
};