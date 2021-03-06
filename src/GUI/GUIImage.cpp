#include "GUIImage.hpp"

GUIImage::GUIImage(const glm::vec4& destRect, GLuint textureID){
     m_destRect = destRect;
     m_textureID = textureID;
}

void GUIImage::render(GUIRenderer& renderer){
     renderer.draw(m_destRect, glm::vec4(0, 0, 1, 1), 0.0f, m_textureID);
}
