#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Utils.hpp"



class Window {
public:
     friend class Engine;

     void create(unsigned int width, unsigned int height, const std::string& name);
     void clear();
     void update();
     void close();

     bool isCloseRequested();

     GLFWwindow* window;


private:

     bool m_closeRequested = false;


};
#endif
