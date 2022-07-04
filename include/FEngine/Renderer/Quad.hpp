#ifndef QUAD_H
#define QUAD_H

#include <GL/glad.h>
#include <glm/glm.hpp>


class QuadVertex {
public:

     glm::vec2 position;
     glm::vec2 uv;

};

class Quad {
public:

     void init();
     void render();
     void destroy();


private:


     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_eboID = 0;


};

#endif
