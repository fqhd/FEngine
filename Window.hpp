#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Settings.hpp"
#include "Utils.hpp"



class Window {
public:

     void create(Settings& settings);
     void clear();
     void update();
     void close();

     GLFWwindow* window;


private:



};
#endif
