#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <GL/glew.h>

#include "Vertex.hpp"


class Terrain{
public:

     void init();
     void render();
     void destroy();

     void uploadData(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

private:


     GLuint m_numVertices = 0;
     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_eboID = 0;

};

#endif
