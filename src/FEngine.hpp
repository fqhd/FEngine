#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "FObject.h"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "Quad.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path, Color color);
    void draw();
    void destroy();
    
    Shader debugShader;
    Skybox skybox;
    Shader shader;
    Window window;
    InputManager inputManager;
    Camera camera;
    Quad quad;
    std::vector<FObject> objects;
};