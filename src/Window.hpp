#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

class Window {
public:

	void create(unsigned int _width, unsigned int _height, const char* _title);
	void clear();
	void update();
	void close();
    bool isOpen();
	GLFWwindow* getWindowPtr();

private:

	GLFWwindow* m_window;

};