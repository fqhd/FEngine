#include "InputManager.hpp"
#include <iostream>

static std::unordered_map<int, bool> keyMap;
static std::unordered_map<int, bool> previousKeyMap;

void keyPressed(int _keyID){
	keyMap[_keyID] = true;
}

void keyReleased(int _keyID){
	keyMap[_keyID] = false;
}

void keyPressedCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods){
	if(_action == GLFW_PRESS){
		keyPressed(_key);
	}else if(_action == GLFW_RELEASE){
		keyReleased(_key);
	}
}

void buttonPressedCallback(GLFWwindow* _window, int _button, int _action, int _mods){
	if(_action == GLFW_PRESS){
		keyPressed(_button);
	}else if(_action == GLFW_RELEASE){
		keyReleased(_button);
	}
}

void InputManager::init(GLFWwindow* _window) {
	m_window = _window;
	glfwSetKeyCallback(_window, keyPressedCallback);
	glfwSetMouseButtonCallback(_window, buttonPressedCallback);
}

void InputManager::processInput() {
	previousKeyMap = keyMap;
	glfwPollEvents();
}

bool InputManager::isKeyDown(int keyID){
	auto it = keyMap.find(keyID);
	if(it != keyMap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(int keyID){
	auto it = previousKeyMap.find(keyID);
	if(it != previousKeyMap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isKeyPressed(int keyID){
	return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(int keyID){
	return (!isKeyDown(keyID) && wasKeyDown(keyID));
}