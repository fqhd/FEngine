#include "GUISlider.hpp"
#include "Utils.hpp"
#include <iostream>

GUISlider::GUISlider(const glm::vec2& position, float size, const ColorRGBA8& lineColor, const ColorRGBA8& buttonColor, float value, Settings& settings){
     m_position = position;
     m_size = size;
     m_lineColor = lineColor;
     m_buttonColor = buttonColor;
     m_buttonRect = glm::vec4(position.x, position.y - settings.sliderButtonHeight / 2, settings.sliderButtonWidth, settings.sliderButtonHeight + 1);
     m_buttonRect.x += value * size;

}

void GUISlider::update(InputManager& manager, Settings& settings){

     m_currentColor = m_buttonColor;

     if(Utils::isInside(manager.getMousePosition(), m_buttonRect)){
          m_currentColor = ColorRGBA8(m_buttonColor.r * 0.6f, m_buttonColor.g * 0.6f, m_buttonColor.b * 0.6f, 255);
          if(manager.isMouseDown(sf::Mouse::Left)){
               m_isSelected = true;
               m_currentColor = ColorRGBA8(m_buttonColor.r * 0.4f, m_buttonColor.g * 0.4f, m_buttonColor.b * 0.4f, 255);
          }
     }

     if(!manager.isMouseDown(sf::Mouse::Left)){
          m_isSelected = false;
     }


     if(m_isSelected){
          m_buttonRect.x = manager.getMousePosition().x - settings.sliderButtonWidth / 2.0f;
          m_currentColor = ColorRGBA8(m_buttonColor.r * 0.4f, m_buttonColor.g * 0.4f, m_buttonColor.b * 0.4f, 255);
     }

     if(m_buttonRect.x < m_position.x){
          m_buttonRect.x = m_position.x;
     }
     if(m_buttonRect.x > m_position.x + m_size - settings.sliderButtonWidth){
          m_buttonRect.x = m_position.x + m_size - settings.sliderButtonWidth;
     }

     m_value = ((m_buttonRect.x - m_position.x)) / ((m_position.x + m_size - settings.sliderButtonWidth) - m_position.x);

}

float GUISlider::getValue(){
     return m_value;
}

void GUISlider::render(GUIRenderer& renderer, GLuint blankTextureID){

     renderer.draw(glm::vec4(m_position, m_size, 1.0f), glm::vec4(0, 0, 1, 1), blankTextureID, m_lineColor); //Rendering the line
     renderer.draw(m_buttonRect, glm::vec4(0, 0, 1, 1), blankTextureID, m_currentColor);

}
