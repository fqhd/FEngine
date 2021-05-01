#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "GUIRenderer.hpp"

#include <glm/glm.hpp>


class GUIImage {
public:

     GUIImage(){}
     GUIImage(const glm::vec4& destRect, GLuint textureID);
     void render(GUIRenderer& renderer);


private:

     glm::vec4 m_destRect;
     GLuint m_textureID = 0;

};

#endif
