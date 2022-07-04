#include "Camera2D.hpp"

void Camera2D::init(unsigned int width, unsigned int height){
     m_matrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
}

const glm::mat4& Camera2D::getMatrix(){
     return m_matrix;
}
