#pragma once
#include <SFML/Window.hpp>
#include "GUIRenderer.hpp"
#include "InputManager.hpp"

class GUICheckbox {
public:

     GUICheckbox(const glm::vec4& destRect, const ColorRGBA8& onColor, const ColorRGBA8& offColor, bool isChecked);
     void update(sf::Window& window, InputManager& manager);
     void render(GUIRenderer& renderer, GLuint blankTextureID);

     bool isChecked();

private:

     bool m_isChecked = false;
     glm::vec4 m_destRect;
     ColorRGBA8 m_offColor;
     ColorRGBA8 m_onColor;
     ColorRGBA8 m_currentColor;

};
