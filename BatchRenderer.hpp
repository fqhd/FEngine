#ifndef BATCHRENDERER_H
#define BATCHRENDERER_H

#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"
#include "GBufferShader.hpp"

class BatchModel {
public:

     BatchModel(unsigned int n, StaticColor c){
          numVertices = n;
          color = c;
     }

     unsigned int numVertices = 0;
     StaticColor color;

};

class BatchRenderer {
public:

     void init();
     void begin();
     void addModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, StaticColor color);
     void end();
     void render(GBufferShader& shader);
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
