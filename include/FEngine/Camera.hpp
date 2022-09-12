#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace FEngine
{
    class Camera
    {
    public:
        void init(unsigned int width, unsigned int height, float fov, float near, float far);
        glm::vec3 position;
        float pitch;
        float yaw;
        float fov;
        float near;
        float far;
        float ar;
        float speed;
        float mouseSensitivity;
        glm::vec3 lightDirection;
        void update();
        const glm::mat4 &getProjection() const;
        const glm::mat4 &getView() const;
        const glm::vec3 getForward() const;

    private:
        glm::mat4 projection;
        glm::mat4 view;
        glm::vec3 previousPosition;
        float previousPitch;
        float previousYaw;
        float previousFov;
    };
}