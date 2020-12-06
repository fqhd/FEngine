#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <unordered_map>
#include "GameStates.hpp"

class InputManager{
public:

	void processInput(sf::Window& window, GameStates& state);

	bool isKeyPressed(unsigned int keyID);
	bool isKeyReleased(unsigned int keyID);
	bool isKeyDown(unsigned int keyID);
	bool wasKeyDown(unsigned int keyID);

	bool isMousePressed(unsigned int keyID);
	bool isMouseReleased(unsigned int keyID);
	bool isMouseDown(unsigned int keyID);
	bool wasMouseDown(unsigned int keyID);

	const glm::vec2& getMousePosition();
	const glm::vec2& getDeltaMousePosition();
	float getDeltaMouseWheel() const ;

private:

	void keyPressed(unsigned int keyID);
	void keyReleased(unsigned int keyID);
	void mousePressed(unsigned int buttonID);
	void mouseReleased(unsigned int buttonID);

	sf::Event m_event;
	std::unordered_map<unsigned int, bool> m_keymap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;

	std::unordered_map<unsigned int, bool> m_mousemap;
	std::unordered_map<unsigned int, bool> m_previousMouseMap;


	glm::vec2 m_mousePosition;
	glm::vec2 m_deltaMousePosition;
	float m_deltaMouseWheel = 0.0f;
};
#endif
