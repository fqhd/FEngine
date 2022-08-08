#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>
#include <iostream>
#include <glm/glm.hpp>

class Window {
public:

	void create(unsigned int _width, unsigned int _height, const char* _title);
	void clear();
	void update();
	void close();
	bool isOpen();
	glm::ivec2 getFramebufferSize();
	GLFWwindow* getWindowPtr();

private:

	glm::ivec2 framebufferSize;
	GLFWwindow* m_window;

};
