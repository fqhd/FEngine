#pragma once

#include "FEngine/Utils/Utils.hpp"
#include "FEngine/Camera/Camera3D.hpp"
#include "Fengine/Utils/InputManager.hpp"


class FirstPersonCamera : public Camera3D {
public:

     void init(unsigned int width, unsigned int height, const glm::vec3& position);
     void update(float deltaTime);

     //Camera Variables
     float mousePitchSensitivity = 0.3f;
     float mouseYawSensitivity = 0.3f;
     float speed = 5.0f;

private:

     float m_pitch = 0.0f;
     float m_yaw = 0.0f;


};
