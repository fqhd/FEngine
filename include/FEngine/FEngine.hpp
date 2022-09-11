#pragma once

#include <FEngine/Window.hpp>
#include <FEngine/InputManager.hpp>
#include <FEngine/Camera.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Shader.hpp>
#include <FEngine/Skybox.hpp>
#include <FEngine/MasterRenderer.hpp>
#include <unordered_map>

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    FObject loadObject(const std::string& path, Color defaultColor);
    void update();
    void draw(const FObject& object);
    void destroy();
    
    Window window;
    InputManager inputManager;
    Camera camera;

private:

    MasterRenderer masterRenderer;
    std::vector<FObject> objects;
    std::unordered_map<std::string, FObject> map;

};