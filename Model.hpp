#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>

#include "Vertex.hpp"

class Model {
public:

     Model(const std::string& model);
     void render();
     void destroy();

private:

     GLuint m_numVertices;
     GLuint m_vaoID;
     GLuint m_vboID;
     GLuint m_eboID;

};

#endif
