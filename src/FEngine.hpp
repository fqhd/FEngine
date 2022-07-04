#pragma once

#include "Window.hpp"
#include "InputManager.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    void draw();
    Window window;
    InputManager inputManager;
};