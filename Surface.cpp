#include "Surface.hpp"
#include <vector>

void Surface::init(Settings& settings){
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

     //Creating and sending the buffer data
     std::vector<Vertex> vertices;

     float offset = settings.worldWidth/2.0f;

     //Triangle
     vertices.push_back(Vertex(glm::vec3(-offset, -offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(-offset, offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     //Triangle
     vertices.push_back(Vertex(glm::vec3(-offset, -offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));
     vertices.push_back(Vertex(glm::vec3(offset, -offset, -offset), glm::vec2(0, 0), glm::vec3(0, 0, 0)));

     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

     glBindBuffer(GL_ARRAY_BUFFER, 0);

     m_numVertices = vertices.size();

}

void Surface::render(){
     glBindVertexArray(m_vaoID);
     glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
     glBindVertexArray(0);
}

void Surface::destroy(){
     glDeleteVertexArrays(1, &m_vaoID);
     glDeleteBuffers(1, &m_vboID);
}
