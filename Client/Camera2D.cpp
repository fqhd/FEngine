#include "Camera2D.hpp"

void Camera2D::createProjectionMatrix(Settings& settings){
     m_projectionMatrix = glm::ortho(0.0f, (float)settings.screenWidth, 0.0f, (float)settings.screenHeight);
}

const glm::mat4& Camera2D::getProjectionMatrix(){
     return m_projectionMatrix;
}
