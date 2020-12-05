#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H

#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"

class BatchModel {
public:

     BatchModel(unsigned int nv, GLuint t){
          numVertices = nv;
          textureID = t;
     }

     unsigned int numVertices = 0;
     GLuint textureID = 0;

};

class BatchRenderer {
public:

     void init();
     void begin();
     void addModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, GLuint textureID);
     void end();
     void render();
     void destroy();



private:

     GLuint m_vaoID = 0;
     GLuint m_vboID = 0;
     GLuint m_eboID = 0;

     std::vector<Vertex> m_vertices;
     std::vector<unsigned int> m_indices;
     std::vector<BatchModel> m_models;

};

#endif
