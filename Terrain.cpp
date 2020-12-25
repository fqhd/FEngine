#include "Terrain.hpp"
#include "Utils.hpp"


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


}

void Terrain::uploadData(Vertex* vertices, unsigned int numVertices){

     //Error checking
     if(!vertices){
          Utils::log("Terrain: null pointer to vertices");
          return;
     }

     //Uploading vertices
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
     glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Terrain::render(IndexBuffer& buffer){
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

     glBindVertexArray(m_vaoID);
     buffer.bind();
     glDrawElements(GL_TRIANGLES, buffer.getNumIndices(), GL_UNSIGNED_INT, 0);
     buffer.unbind();
     glBindVertexArray(0);

     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void Terrain::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
}
