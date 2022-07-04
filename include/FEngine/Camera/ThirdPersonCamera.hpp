#ifndef THIRD_PERSON_CAMERA_H
#define THIRD_PERSON_CAMERA_H

#include "Camera3D.hpp"
#include "../Utils/InputManager.hpp"


class ThirdPersonCamera : public Camera3D {
public:

     void init(unsigned int width, unsigned int height, const glm::vec3& center, const glm::vec3& position);

     void update();
     glm::vec3 center;
     float horizontalSensitivity = 0.5f;
     float verticalSensitivity = 0.5f;
     float zoomSensitivity = 2.5f;
     float speed = 0.05f;
     float minDistance = 1.0f;



private:

     //Camera Functions
     void calculatePitch();
     void calculateYaw();
     void calculateZoom();
     void calculateTargetPosition(float horizDistance, float verticDistance);
     float calculateHorizontalDistance();
     float calculateVerticalDistance();

     //Camera Variables
     glm::vec3 m_targetPosition;
     float m_distanceFromCenter = 32.0f;
     float m_pitch = 45.0f;
     float m_yaw = 0.0f;

};

#endif
