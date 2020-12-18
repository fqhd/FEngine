#ifndef WINDOW_H
#define WINDOW_H


#include <GL/glew.h>

#include "Utils.hpp"
#include "InputManager.hpp"



class Window {
public:

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
