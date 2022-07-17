#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>


class InputManager {
public:

	void init(GLFWwindow* _window);
	void processInput();

	bool isKeyPressed(int _keyID);
	bool isKeyReleased(int _keyID);
	bool isKeyDown(int _keyID);
	bool wasKeyDown(int _keyID);

private:

	GLFWwindow* m_window;

};