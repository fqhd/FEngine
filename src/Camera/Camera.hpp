#ifndef CAMERA_H
#define CAMERA_H

#include "FirstPersonCamera.hpp"
#include "ThirdPersonCamera.hpp"


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum class CameraMode {
     FIRST_PERSON, THIRD_PERSON
};


class Camera {
public:

     FirstPersonCamera firstPersonCamera;
     ThirdPersonCamera thirdPersonCamera;

     void setMode(GLFWwindow* window, CameraMode mode);

     const glm::mat4& getProjectionMatrix();
     const glm::mat4& getViewMatrix();
     const glm::vec3& getDirection();
     const glm::vec3& getPosition();

private:

     CameraMode m_mode = CameraMode::THIRD_PERSON;

};

#endif
