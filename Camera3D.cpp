#include "Camera3D.hpp"

void Camera3D::init(unsigned int width, unsigned int height){
     m_projectionMatrix = glm::perspective(glm::radians(90.0f), width/(float)height, 0.1f, 1000.0f);
     position = glm::vec3(0.0f, 0.0f, 0.0f);
     up = glm::vec3(0.0f, 1.0f, 0.0f);
     forward = glm::vec3(0.0f, 0.0f, -1.0f);
}

const Camera3D::glm::mat4& getViewMatrix(){
     if(!m_needsUpdate)
          return m_viewMatrix;

     m_viewMatrix = glm::lookAt(position, position + forward, up);

     return m_viewMatrix;
}

const Camera3D::glm::mat4& getProjectionMatrix() const{
     return m_projectionMatrix;
}
