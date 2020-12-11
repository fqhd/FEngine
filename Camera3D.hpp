#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.hpp"
#include "Settings.hpp"

class Camera3D {
public:

     void init(unsigned int width, unsigned int height);
     void move(InputManager& manager, Settings& settings, float deltaTime);
     const glm::mat4& getViewMatrix();

     const glm::mat4& getProjectionMatrix() const;

     glm::vec3 position;
     glm::vec3 forward;
     glm::vec3 up;
     glm::vec3 center;


private:

     void calculatePitch(InputManager& manager, Settings& settings);
     void calculateYaw(InputManager& manager, Settings& settings);
     void calculateZoom(InputManager& manager, Settings& settings);
     void calculateTargetPosition(float horizDistance, float verticDistance);
     float calculateHorizontalDistance();
     float calculateVerticalDistance();

     bool m_needsUpdate = true;
     glm::mat4 m_projectionMatrix;
     glm::mat4 m_viewMatrix;
     glm::vec3 m_targetPosition;

     float m_distanceFromCenter = 20.0f;
     float m_pitch = 0.0f;
     float m_yaw = 0.0f;

};

#endif
