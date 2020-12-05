#pragma once
#include "GUIRenderer.hpp"
#include "InputManager.hpp"
#include "Settings.hpp"

class GUISlider {
public:

     GUISlider(const glm::vec2& position, float size, const ColorRGBA8& lineColor, const ColorRGBA8& buttonColor, float value, Settings& settings);
     void update(InputManager& manager, Settings& settings);
     void render(GUIRenderer& renderer, GLuint blankTextureID);

     float getValue();

private:

     float m_value = 0.0f;
     bool m_isSelected = false;
     glm::vec4 m_buttonRect;
     glm::vec2 m_position;
     float m_size = 0.0f;
     ColorRGBA8 m_lineColor;
     ColorRGBA8 m_buttonColor;
     ColorRGBA8 m_currentColor;

};
