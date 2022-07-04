#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/gtc/matrix_transform.hpp>

#include "../Utils/InputManager.hpp"


class Camera3D {
public:

     const glm::mat4& getProjectionMatrix();
     const glm::mat4& getViewMatrix();
     const glm::vec3& getPosition();
     const glm::vec3& getDirection();

protected:
     
     void createProjectionMatrix(unsigned int width, unsigned int height);
     void updateViewMatrix();

     glm::mat4 m_projectionMatrix;
     glm::mat4 m_viewMatrix;
     glm::vec3 m_position;
     glm::vec3 m_direction;

};

#endif
