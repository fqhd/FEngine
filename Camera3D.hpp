#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.hpp"

class Camera3D {
public:

     void init(unsigned int width, unsigned int height);
     void move(InputManager& manager);
     const glm::mat4& getViewMatrix();

     const glm::mat4& getProjectionMatrix() const;

     glm::vec3 position;
     glm::vec3 forward;
     glm::vec3 up;

private:

     void calculatePitch(InputManager& manager);
     void calculateYaw(InputManager& manager);
     void calculateZoom(InputManager& manager);
     void calculateCameraPosition(float horizDistance, float verticDistance);
     float calculateHorizontalDistance();
     float calculateVerticalDistance();

     bool m_needsUpdate = true;
     glm::mat4 m_projectionMatrix;
     glm::mat4 m_viewMatrix;

     float m_distanceFromCenter = 20.0f;
     float m_pitch = 0.0f;
     float m_yaw = 0.0f;

};

#endif
