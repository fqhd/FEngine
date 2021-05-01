#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/gtc/matrix_transform.hpp>


class Camera2D {
public:

     void init(unsigned int width, unsigned int height);

     const glm::mat4& getMatrix();

private:

     glm::mat4 m_matrix;


};

#endif
