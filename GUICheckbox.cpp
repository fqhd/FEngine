#include "Utils.hpp"
#include "GUICheckbox.hpp"

GUICheckbox::GUICheckbox(const glm::vec4& destRect, const ColorRGBA8& onColor, const ColorRGBA8& offColor, bool isChecked){
     m_destRect = destRect;
     m_onColor = onColor;
     m_offColor = offColor;
	m_isChecked = isChecked;
}

void GUICheckbox::update(InputManager& manager){

     ColorRGBA8 color = m_isChecked ? m_onColor : m_offColor;

     m_currentColor = color;
     if(Utils::isInside(manager.getMousePosition(), m_destRect)){
          m_currentColor = ColorRGBA8(color.r * 0.6f, color.g * 0.6f, color.b * 0.6f, color.a);
          if(manager.isMouseDown(sf::Mouse::Left)){
               m_currentColor = ColorRGBA8(color.r * 0.3f, color.g * 0.3f, color.b * 0.3f, color.a);
          }else if(manager.isMouseReleased(sf::Mouse::Left)){
               m_isChecked = !m_isChecked;
          }
     }

}

void GUICheckbox::render(GUIRenderer& renderer, GLuint blankTextureID){
     renderer.draw(glm::vec4(m_destRect.x - 1, m_destRect.y - 1, m_destRect.z + 2, m_destRect.z + 2), glm::vec4(0, 0, 1, 1), blankTextureID, ColorRGBA8(100, 100, 100, 255));
     renderer.draw(m_destRect, glm::vec4(0, 0, 1, 1), blankTextureID, m_currentColor);
}


bool GUICheckbox::isChecked(){
     return m_isChecked;
}
