#include "Camera3D.hpp"

void Camera3D::createProjectionMatrix(unsigned int width, unsigned int height){
     m_projectionMatrix = glm::perspective(glm::radians(90.0f), width/(float)height, 0.1f, 1000.0f);
}


const glm::mat4& Camera3D::getProjectionMatrix(){
     return m_projectionMatrix;
}

const glm::mat4& Camera3D::getViewMatrix(){
     return m_viewMatrix;
}

const glm::vec3& Camera3D::getPosition(){
     return m_position;
}

const glm::vec3& Camera3D::getDirection(){
     return m_position;
}

void Camera3D::updateViewMatrix(){
     m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, glm::vec3(0, 1, 0));
}
