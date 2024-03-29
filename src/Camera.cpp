#include <FEngine/Camera.hpp>
#include <iostream>

namespace FEngine
{
    void Camera::init(unsigned int w, unsigned int h, float f, float n, float farPlane)
    {
        ar = w / (float)h;
        position = glm::vec3(0.0f);
        fov = f;
        near = n;
        yaw = 0.0f;
        pitch = 0.0f;
        far = farPlane;
        lightDirection = glm::normalize(glm::vec3(0.5, 1.0, -0.7));
        speed = 2.5f;
        mouseSensitivity = 0.3f;
    }

    void Camera::update()
    {
        if (pitch != previousPitch || yaw != previousYaw || position != previousPosition)
        {
            previousPitch = pitch;
            previousYaw = yaw;
            previousPosition = position;
            glm::vec3 direction = getForward();
            view = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
        }
        if (fov != previousFov)
        {
            projection = glm::perspective(glm::radians(fov), ar, near, far);
        }
    }

    const glm::mat4 &Camera::getProjection() const
    {
        return projection;
    }

    const glm::mat4 &Camera::getView() const
    {
        return view;
    }

    const glm::vec3 Camera::getForward() const
    {
        glm::vec3 direction;
        direction.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        return direction;
    }
}