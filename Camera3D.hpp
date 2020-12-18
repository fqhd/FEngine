#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.hpp"

class Camera3D {
public:

     void init(unsigned int width, unsigned int height);
     void update();
     const glm::mat4& getViewMatrix();

     const glm::mat4& getProjectionMatrix() const;

     glm::vec3 position;
     glm::vec3 forward;
     glm::vec3 up;
     glm::vec3 center;


private:

     void calculatePitch();
     void calculateYaw();
     void calculateZoom();
     void calculateTargetPosition(float horizDistance, float verticDistance);
     float calculateHorizontalDistance();
     float calculateVerticalDistance();

     bool m_needsUpdate = true;
     glm::mat4 m_projectionMatrix;
     glm::mat4 m_viewMatrix;
     glm::vec3 m_targetPosition;

     float m_distanceFromCenter = 32.0f;
     float m_pitch = 45.0f;
     float m_yaw = 0.0f;

};

#endif
