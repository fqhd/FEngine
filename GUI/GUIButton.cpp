#include "GUIButton.hpp"
#include "Utils.hpp"

GUIButton::GUIButton(const glm::vec4& destRect, GLuint textureID){
	m_destRect = destRect;
	m_textureID = textureID;
}

void GUIButton::update(){
	m_textureIndex = 0;
	m_isPressed = false;

	if(Utils::isInside(InputManager::getMousePosition(), m_destRect)){
		m_textureIndex = 1;
		if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
			m_textureIndex = 2;
		}else if(InputManager::isButtonReleased(GLFW_MOUSE_BUTTON_LEFT)){
			m_isPressed = true;
		}
	}

}

void GUIButton::render(GUIRenderer& renderer){

	renderer.draw(m_destRect, glm::vec4(0, m_textureIndex / 3.0f, 1, 1.0f / 3.0f), 1.0f, m_textureID);

}

bool GUIButton::isPressed(){
	return m_isPressed;
}
