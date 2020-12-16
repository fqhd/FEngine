#include "Camera3D.hpp"

#include <iostream>


const float HORIZONTAL_SENSITITY = 0.3f;
const float VERTICAL_SENSITIVITY = 0.3f;
const float ZOOM_SENSITIVITY = 0.3f;
const float CAMERA_SPEED = 0.5f;

void Camera3D::init(unsigned int width, unsigned int height){
     m_projectionMatrix = glm::perspective(glm::radians(90.0f), width/(float)height, 0.1f, 1000.0f);
     position = glm::vec3(0.0f, 0.0f, 0.0f);
     up = glm::vec3(0.0f, 1.0f, 0.0f);
     forward = glm::vec3(0.0f, 0.0f, 1.0f);
     center = glm::vec3(0.0f, 0.0f, 0.0f);
}

const glm::mat4& Camera3D::getViewMatrix(){
     if(!m_needsUpdate)
          return m_viewMatrix;

     m_viewMatrix = glm::lookAt(position, center, up);

     return m_viewMatrix;
}

const glm::mat4& Camera3D::getProjectionMatrix() const{
     return m_projectionMatrix;
}

void Camera3D::move(){

     //Calculating variables
     calculatePitch();
     calculateYaw();
     calculateZoom();
     float horizDistance = calculateHorizontalDistance();
     float verticDistance = calculateVerticalDistance();
     calculateTargetPosition(horizDistance, verticDistance);

     position += (m_targetPosition - position) * CAMERA_SPEED;

}

void Camera3D::calculateTargetPosition(float horizDistance, float verticDistance) {
     m_targetPosition.y = center.y + verticDistance;
     float offsetX = (float)(horizDistance * glm::sin(glm::radians(m_yaw)));
     float offsetZ = (float)(horizDistance * glm::cos(glm::radians(m_yaw)));
     m_targetPosition.x = center.x - offsetX;
     m_targetPosition.z = center.z - offsetZ;
}

float Camera3D::calculateHorizontalDistance() {
     return (float) (m_distanceFromCenter * glm::cos(glm::radians(m_pitch)));
}

float Camera3D::calculateVerticalDistance() {
     return (float) (m_distanceFromCenter * glm::sin(glm::radians(m_pitch)));
}

void Camera3D::calculatePitch(){
     if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
          m_pitch += InputManager::getDeltaMousePosition().y * VERTICAL_SENSITIVITY;
     }
     if(m_pitch < -89.0f){
          m_pitch = -89.0f;
     }
     if(m_pitch > 89.0f){
          m_pitch = 89.0f;
     }

}

void Camera3D::calculateYaw(){
     if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
          m_yaw -= InputManager::getDeltaMousePosition().x * HORIZONTAL_SENSITITY;
     }
}

void Camera3D::calculateZoom(){
     m_distanceFromCenter -= InputManager::getDeltaMouseWheel() * ZOOM_SENSITIVITY;
     if(m_distanceFromCenter < 5.0f){
          m_distanceFromCenter = 5.0f;
     }

}
