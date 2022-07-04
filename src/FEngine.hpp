#pragma once

#include "Window.hpp"

class FEngine {
public:

    FEngine(const char* title, int width, int height);
    void draw();
    Window window;

};