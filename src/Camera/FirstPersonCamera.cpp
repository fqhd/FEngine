#include "FirstPersonCamera.hpp"



void FirstPersonCamera::init(unsigned int width, unsigned int height, const glm::vec3& position){
     createProjectionMatrix(width, height);
     m_position = position;
     m_direction = glm::vec3(0.0, 0.0, 1.0);
}

void FirstPersonCamera::update(float deltaTime){

     //Movement
     glm::vec3 forward = glm::normalize(glm::vec3(m_direction.x, 0.0f, m_direction.z));
     glm::vec3 side = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
     if(InputManager::isKeyDown(GLFW_KEY_W)){
          m_position += forward * speed * deltaTime;
     }
     if(InputManager::isKeyDown(GLFW_KEY_S)){
          m_position -= forward * speed * deltaTime;
     }
     if(InputManager::isKeyDown(GLFW_KEY_A)){
          m_position -= side * speed * deltaTime;
     }
     if(InputManager::isKeyDown(GLFW_KEY_D)){
          m_position += side * speed * deltaTime;
     }
     if(InputManager::isKeyDown(GLFW_KEY_SPACE)){
          m_position += glm::vec3(0, 1, 0) * speed * deltaTime;
     }
     if(InputManager::isKeyDown(GLFW_KEY_LEFT_SHIFT)){
          m_position -= glm::vec3(0, 1, 0) * speed * deltaTime;
     }

     m_pitch -= InputManager::getDeltaMousePosition().y * mousePitchSensitivity;
     m_yaw += InputManager::getDeltaMousePosition().x * mouseYawSensitivity;

     //Capping the piatch
     if(m_pitch > 89.0f) m_pitch = 89.0f;
     if(m_pitch < -89.0f) m_pitch = -89.0f;

     m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
     m_direction.y = sin(glm::radians(m_pitch));
     m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
     m_direction = glm::normalize(m_direction);

     updateViewMatrix();

}
