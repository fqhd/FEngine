#include "Model.hpp"
#include "OBJLoader.hpp"


void Model::loadFromFile(const std::string& path){

     //Initializing the vao
     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);

     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

     //Creating and sending data to VBO
     IndexedModel model = OBJModel(path).ToIndexedModel();

     std::vector<Vertex> vertices;

     for(unsigned int i = 0; i < model.positions.size(); i++){
          vertices.push_back(Vertex(model.positions[i], model.normals[i]));
     }

     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

     glBindBuffer(GL_ARRAY_BUFFER, 0);

     //Sending indices to EBO
     glGenBuffers(1, &m_eboID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);

     //Sending indices and unbinding vao
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);

     glBindVertexArray(0);

     m_numVertices = model.indices.size();


}


void Model::render(){

     glBindVertexArray(m_vaoID);
     glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);

}

void Model::destroy(){

     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
     glDeleteBuffers(1, &m_eboID);

}
