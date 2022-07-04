#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <GL/glad.h>

#include "../Renderer/Vertex.hpp"
#include "../Utils/IndexBuffer.hpp"


class Terrain {
public:

     void init();
     void render(IndexBuffer& buffer);
     void destroy();

     void uploadData(Vertex* vertices, unsigned int numVertices);

private:


     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;

};

#endif
