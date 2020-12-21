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

     void uploadData(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

private:

     GLuint m_numVertices = 0;
     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_eboID = 0;

};

#endif
