#include "Terrain.hpp"

void Terrain::init(){

     //Creating VAO and uploading data
     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     //Creating and binding buffer
     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     //Enabling VAO attributes
     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);
     glEnableVertexAttribArray(2);

     //Telling opengl how to store the data from this buffer into the specified attributes of the VAO
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

     //Unbiding buffer
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

     //Creating buffer to render with indices
     glGenBuffers(1, &m_eboID);

}

void Terrain::uploadData(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices){

     //Uploading vertices
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
     glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     //Uploading indices
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     m_numVertices = indices.size();

}

void Terrain::render(){

     glBindVertexArray(m_vaoID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     glBindVertexArray(0);

}

void Terrain::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
     glDeleteBuffers(1, &m_eboID);
}
