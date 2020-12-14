#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Window.hpp"
#include "GameStates.hpp"
#include "Settings.hpp"

#include <unordered_map>



class InputManager {
public:

	static void init(GLFWwindow* window);
	static void processInput(GLFWwindow* window, GameStates& state, Settings& settings);

	static bool isKeyPressed(unsigned int keyID);
	static bool isKeyReleased(unsigned int keyID);
	static bool isKeyDown(unsigned int keyID);
	static bool wasKeyDown(unsigned int keyID);

	static bool isButtonPressed(unsigned int keyID);
	static bool isButtonReleased(unsigned int keyID);
	static bool isButtonDown(unsigned int keyID);
	static bool wasButtonDown(unsigned int keyID);

	static const glm::vec2& getMousePosition();
	static const glm::vec2& getDeltaMousePosition();
	static float getDeltaMouseWheel();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


private:

	static void keyPressed(unsigned int keyID);
	static void keyReleased(unsigned int keyID);
	static void buttonPressed(unsigned int buttonID);
	static void buttonReleased(unsigned int buttonID);

	static std::unordered_map<unsigned int, bool> m_keymap;
	static std::unordered_map<unsigned int, bool> m_previousKeyMap;

	static std::unordered_map<unsigned int, bool> m_mousemap;
	static std::unordered_map<unsigned int, bool> m_previousMouseMap;


	static glm::vec2 m_mousePosition;
	static glm::vec2 m_deltaMousePosition;
	static float m_deltaMouseWheel;

};
#endif
