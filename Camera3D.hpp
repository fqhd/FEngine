#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <glm/gtc/matrix_transform.hpp>

class Camera3D {
public:

     void init(unsigned int width, unsigned int height);
     const glm::mat4& getViewMatrix();
     const glm::mat4& getProjectionMatrix() const;

     glm::vec3 position;
     glm::vec3 forward;
     glm::vec3 up;

private:

     bool m_needsUpdate = true;
     glm::mat4 m_projectionMatrix;
     glm::mat4 m_viewMatrix;

};

#endif
