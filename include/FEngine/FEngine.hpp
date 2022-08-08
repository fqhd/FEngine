#pragma once

#include <FEngine/Window.hpp>
#include <FEngine/InputManager.hpp>
#include <FEngine/Camera.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Shader.hpp>
#include <FEngine/Skybox.hpp>
#include <FEngine/MasterRenderer.hpp>

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
    std::vector<FObject> objects;
};