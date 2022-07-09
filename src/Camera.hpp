#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:

	void init(unsigned int width, unsigned int height, float fov, float near, float far);
    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
    glm::vec3 position;
    float pitch;
    float yaw;
    float fov;
    float near;
    float far;
    float width;
    float height;
    glm::vec3 lightDirection;

};