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
     glEnableVertexAttribArray(2);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

     //Sending indices to EBO
     glGenBuffers(1, &m_eboID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);


     glBindVertexArray(0);

}

void BatchRenderer::begin(){
     m_vertices.clear();
     m_indices.clear();
     m_models.clear();
}

void BatchRenderer::addModel(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, GLuint textureID){
     //Adding vertices
     for(unsigned int i = 0; i < numVertices; i++){
          m_vertices.push_back(vertices[i]);
     }

     //Adding indices
     for(unsigned int i = 0; i < numIndices; i++){
          m_indices.push_back(indices[i]);
     }

     std::cout << "Numvertices: " << m_vertices.size() << std::endl;
     std::cout << "numindices: " << m_indices.size() << std::endl;
     //Adding Model
     if(m_models.empty()){
          //Create new model
          m_models.emplace_back(BatchModel(numIndices, textureID));
     }
     else if(m_models.back().textureID != textureID){
          //Increase vertices for previous model
          m_models.back().numVertices += numIndices;
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

}

void BatchRenderer::render(){
     glBindVertexArray(m_vaoID);
     for(unsigned int i = 0; i < m_models.size(); i++){
          if(i == 0){
               glDrawElements(GL_TRIANGLES, m_models[i].numVertices, GL_UNSIGNED_INT, 0);
          }else{
               glDrawElements(GL_TRIANGLES, m_models[i].numVertices, GL_UNSIGNED_INT, (void*)m_models[i - 1].numVertices);
          }
     }
     glBindVertexArray(m_eboID);
}

void BatchRenderer::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
     glDeleteBuffers(1, &m_eboID);
}
