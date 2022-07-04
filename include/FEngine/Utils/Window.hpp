#pragma once

#include <GL/glad.h>

#include "Utils.hpp"
#include "InputManager.hpp"


class Window {
public:

     void create(unsigned int width, unsigned int height, const std::string& name, bool resizable, bool decorated);
     void clear();
     void update();
     void close();

     bool isCloseRequested();

     GLFWwindow* window;


private:

     bool m_closeRequested = false;


};