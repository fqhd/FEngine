#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/gtc/matrix_transform.hpp>
#include "Settings.hpp"


class Camera2D {
public:

     void createProjectionMatrix(Settings& settings);

     const glm::mat4& getProjectionMatrix();

private:

     glm::mat4 m_projectionMatrix;


};

#endif
