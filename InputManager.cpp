#include "InputManager.hpp"

#include "Utils.hpp"
#include <iostream>

void InputManager::processInput(GameStates& state, Settings& settings){

	m_previousKeyMap = m_keymap;
	m_previousMouseMap = m_mousemap;
	m_deltaMouseWheel = 0;

	while(SDL_PollEvent(&m_event)){
		switch(m_event.type){
		case SDL_QUIT:
			state = GameStates::EXIT;
		break;
		case SDL_KEYDOWN:
			keyPressed(m_event.key.keysym.sym);
		break;
		case SDL_KEYUP:
			keyReleased(m_event.key.keysym.sym);
		break;
		case SDL_MOUSEBUTTONDOWN:
			mousePressed(m_event.button.button);
		break;
		case SDL_MOUSEBUTTONUP:
			mouseReleased(m_event.button.button);
		break;
		case SDL_MOUSEWHEEL:
			m_deltaMouseWheel = m_event.wheel.y;
		break;
		}
	}

	//Updating the mouse position/delta mouse position
	glm::ivec2 tempPosition;
	SDL_GetMouseState(&tempPosition.x, &tempPosition.y);
	tempPosition.y = settings.screenHeight - tempPosition.y;
	m_deltaMousePosition = m_mousePosition - tempPosition;
	m_mousePosition = tempPosition;

}

float InputManager::getDeltaMouseWheel() const {
	return m_deltaMouseWheel;
}

const glm::ivec2& InputManager::getDeltaMousePosition() {
	return m_deltaMousePosition;
}

const glm::ivec2& InputManager::getMousePosition() {
	return m_mousePosition;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	return (isKeyDown(keyID) && !wasKeyDown(keyID));
}

bool InputManager::isKeyReleased(unsigned int keyID){
	return (!isKeyDown(keyID) && wasKeyDown(keyID));
}

bool InputManager::isMousePressed(unsigned int keyID){
	return (isMouseDown(keyID) && !wasMouseDown(keyID));
}

bool InputManager::isMouseReleased(unsigned int keyID){
	return (!isMouseDown(keyID) && wasMouseDown(keyID));
}


bool InputManager::isKeyDown(unsigned int keyID){
	auto it = m_keymap.find(keyID);
	if(it != m_keymap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::isMouseDown(unsigned int buttonID){
	auto it = m_mousemap.find(buttonID);
	if(it != m_mousemap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasKeyDown(unsigned int buttonID){
	auto it = m_previousKeyMap.find(buttonID);
	if(it != m_previousKeyMap.end()){
		return it->second;
	}
	return false;
}

bool InputManager::wasMouseDown(unsigned int buttonID){
	auto it = m_previousMouseMap.find(buttonID);
	if(it != m_previousMouseMap.end()){
		return it->second;
	}
	return false;
}

void InputManager::mousePressed(unsigned int buttonID){
	m_mousemap[buttonID] = true;
}

void InputManager::mouseReleased(unsigned int buttonID){
	m_mousemap[buttonID] = false;
}

void InputManager::keyPressed(unsigned int keyID){
	m_keymap[keyID] = true;
}

void InputManager::keyReleased(unsigned int keyID){
	m_keymap[keyID] = false;
}
