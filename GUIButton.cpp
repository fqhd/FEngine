#include "GUIButton.hpp"
#include "Utils.hpp"

GUIButton::GUIButton(const glm::vec4& destRect, const ColorRGBA8& color){
	m_destRect = destRect;
	m_baseColor = color;
}

void GUIButton::update(InputManager& manager){

	m_currentColor = m_baseColor;
	m_isPressed = false;

	if(Utils::isInside(manager.getMousePosition(), m_destRect)){
		m_currentColor = ColorRGBA8(m_baseColor.r * 0.8f, m_baseColor.g * 0.8f, m_baseColor.b * 0.8f, m_baseColor.a);
		if(manager.isMouseDown(sf::Mouse::Left)){
			m_currentColor = ColorRGBA8(m_baseColor.r * 0.6f, m_baseColor.g * 0.6f, m_baseColor.b * 0.6f, m_baseColor.a);
		}else if(manager.isMouseReleased(sf::Mouse::Left)){
			m_isPressed = true;
		}
	}


}

void GUIButton::render(GUIRenderer& renderer, GLuint blankTextureID){
	renderer.draw(m_destRect, glm::vec4(0, 0, 1, 1), blankTextureID, m_currentColor);
}

bool GUIButton::isPressed(){
	return m_isPressed;
}
