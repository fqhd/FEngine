#pragma once

#include <FEngine/Window.hpp>
#include <FEngine/InputManager.hpp>
#include <FEngine/Camera.hpp>
#include <FEngine/FObject.hpp>
#include <FEngine/Shader.hpp>
#include <FEngine/Skybox.hpp>
#include <FEngine/MasterRenderer.hpp>
#include <FEngine/Timer.hpp>
#include <unordered_map>

namespace FEngine
{
    class FEngine
    {
    public:
        FEngine(const char *title, int width, int height);
        FObject loadObject(const std::string &path, Color defaultColor);
        void update();
        void draw(const FObject &object);
        void destroy();
        void firstPersonCamera(bool enabled);
        float getDeltaTime();

        Window window;
        InputManager inputManager;
        Camera camera;

    private:
        Timer timer;
        MasterRenderer masterRenderer;
        std::vector<FObject> objects;
        std::unordered_map<std::string, FObject> map;
        bool fpCam;
        float deltaTime;
        void firstPersonInput(float deltaTime);
    };
}