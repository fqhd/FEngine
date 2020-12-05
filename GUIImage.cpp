#include "GUIImage.hpp"

GUIImage::GUIImage(const glm::vec4& destRect, GLuint textureID, const ColorRGBA8& color){
     m_destRect = destRect;
     m_textureID = textureID;
     m_color = color;
}

void GUIImage::render(GUIRenderer& renderer){
     renderer.draw(m_destRect, glm::vec4(0, 0, 1, 1), m_textureID, m_color);
}
