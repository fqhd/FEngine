#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:

	Camera(unsigned int width, unsigned int height, float fov);
    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
    glm::vec3 position;
    float pitch;
    float yaw;
    float fov;

private:
    float ar;

};