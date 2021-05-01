#include "ThirdPersonCamera.hpp"



void ThirdPersonCamera::init(unsigned int width, unsigned int height, const glm::vec3& center, const glm::vec3& position){
     createProjectionMatrix(width, height);
     m_distanceFromCenter = glm::abs(glm::length(position - center));
     this->center = center;
     m_position = glm::vec3(0, 0, 0);
     m_targetPosition = position;
}

void ThirdPersonCamera::update(){

     //Calculating variables
     calculatePitch();
     calculateYaw();
     calculateZoom();
     float horizDistance = calculateHorizontalDistance();
     float verticDistance = calculateVerticalDistance();
     calculateTargetPosition(horizDistance, verticDistance);

     m_position += (m_targetPosition - m_position) * speed;
     m_direction = center - m_position;

     updateViewMatrix();

}

void ThirdPersonCamera::calculateTargetPosition(float horizDistance, float verticDistance) {
     m_targetPosition.y = center.y + verticDistance;
     float offsetX = (float)(horizDistance * glm::sin(glm::radians(m_yaw)));
     float offsetZ = (float)(horizDistance * glm::cos(glm::radians(m_yaw)));
     m_targetPosition.x = center.x - offsetX;
     m_targetPosition.z = center.z - offsetZ;
}

float ThirdPersonCamera::calculateHorizontalDistance() {
     return (float) (m_distanceFromCenter * glm::cos(glm::radians(m_pitch)));
}

float ThirdPersonCamera::calculateVerticalDistance() {
     return (float) (m_distanceFromCenter * glm::sin(glm::radians(m_pitch)));
}

void ThirdPersonCamera::calculatePitch(){
     if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
          m_pitch += InputManager::getDeltaMousePosition().y * verticalSensitivity;
     }
     if(m_pitch < -89.0f){
          m_pitch = -89.0f;
     }
     if(m_pitch > 89.0f){
          m_pitch = 89.0f;
     }

}

void ThirdPersonCamera::calculateYaw(){
     if(InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)){
          m_yaw -= InputManager::getDeltaMousePosition().x * horizontalSensitivity;
     }
}

void ThirdPersonCamera::calculateZoom(){
     m_distanceFromCenter -= InputManager::getDeltaMouseWheel() * zoomSensitivity;
     if(m_distanceFromCenter < minDistance){
          m_distanceFromCenter = minDistance;
     }

}
