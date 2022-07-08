#include "Camera.hpp"
#include <iostream>

void Camera::init(unsigned int width, unsigned int height, float f, float n, float farPlane){
    ar = width / (float)height;
	position = glm::vec3(0);
    fov = f;
    near = n;
    far = farPlane;
}

glm::mat4 Camera::getProjection() const {
	return glm::perspective(glm::radians(fov), ar, 0.1f, 1000.0f);
}

glm::mat4 Camera::getView() const {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	return glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
}
