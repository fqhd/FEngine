#include <FEngine/Camera.hpp>
#include <iostream>

void Camera::init(unsigned int w, unsigned int h, float f, float n, float farPlane){
    ar = w / (float)h;
	position = glm::vec3(0);
    fov = f;
    near = n;
    far = farPlane;
    lightDirection = glm::normalize(glm::vec3(0.5, 1.0, -0.7));
}

void Camera::update(){
    if(pitch != previousPitch || yaw != previousYaw || position != previousPosition){
        previousPitch = pitch;
        previousYaw = yaw;
        previousPosition = position;
        glm::vec3 direction;
        direction.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
    }
    if(fov != previousFov){
        projection = glm::perspective(glm::radians(fov), ar, near, far);
    }
}

const glm::mat4& Camera::getProjection() const {
    return projection;
}

const glm::mat4& Camera::getView() const {
    return view;
}
