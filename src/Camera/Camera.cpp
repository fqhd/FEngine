#include "Camera.hpp"


void Camera::setMode(GLFWwindow* window, CameraMode mode){
     m_mode = mode;
     switch(mode){
          case CameraMode::FIRST_PERSON:
               glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
          break;
          case CameraMode::THIRD_PERSON:
               glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
          break;
     }
}


const glm::mat4& Camera::getProjectionMatrix(){
     return m_mode == CameraMode::FIRST_PERSON ? firstPersonCamera.getProjectionMatrix() : thirdPersonCamera.getProjectionMatrix();
}

const glm::mat4& Camera::getViewMatrix(){
     return m_mode == CameraMode::FIRST_PERSON ? firstPersonCamera.getViewMatrix() : thirdPersonCamera.getViewMatrix();
}

const glm::vec3& Camera::getDirection(){
     return m_mode == CameraMode::FIRST_PERSON ? firstPersonCamera.getDirection() : thirdPersonCamera.getDirection();
}

const glm::vec3& Camera::getPosition(){
     return m_mode == CameraMode::FIRST_PERSON ? firstPersonCamera.getPosition() : thirdPersonCamera.getPosition();
}
