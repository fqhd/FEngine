#include "BatchRenderer.hpp"

#include <iostream>


void BatchRenderer::init(){

     //Initializing the vao
     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

     glBindVertexArray(0);

     glGenBuffers(1, &m_eboID);
}

void BatchRenderer::begin(){
     m_vertices.clear();
     m_indices.clear();
     m_models.clear();
}

void BatchRenderer::addModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, StaticColor color){

     //Adding vertices
     for(unsigned int i = 0; i < numVertices; i++){
          m_vertices.push_back(vertices[i]);
     }

     //Adding indices
     for(unsigned int i = 0; i < numIndices; i++){
          m_indices.push_back(indices[i]);
     }

     //If previous model had same color use the same color
     if(m_models.empty()){
          m_models.push_back(BatchModel(numIndices, color));
     } else if (m_models.back().color.r == color.r && m_models.back().color.g == color.g && m_models.back().color.b == color.b) {
          m_models.back().numVertices += numIndices;
     }else{
          m_models.push_back(BatchModel(numIndices, color));
     }

}

void BatchRenderer::end(){

     //Sending vertices to VBO
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
     glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     //Sending indices to EBO
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), m_indices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void BatchRenderer::render(GBufferShader& shader){
     shader.loadModelMatrix(glm::mat4(1.0f));

     glBindVertexArray(m_vaoID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);

     for(unsigned int i = 0; i < m_models.size(); i++){
          shader.loadColor(m_models[i].color);
          if(i == 0){
               glDrawElements(GL_TRIANGLES, m_models[i].numVertices, GL_UNSIGNED_INT, 0);
          }else{
               glDrawElements(GL_TRIANGLES, m_models[i].numVertices, GL_UNSIGNED_INT, (void*)m_models[i - 1].numVertices);
          }
     }

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     glBindVertexArray(m_eboID);
}

void BatchRenderer::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
     glDeleteBuffers(1, &m_eboID);
}
