#include "Quad.hpp"

void Quad::init(){

     glGenVertexArrays(1, &m_vaoID);
     glBindVertexArray(m_vaoID);

     glGenBuffers(1, &m_vboID);
     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

     glEnableVertexAttribArray(0);
     glEnableVertexAttribArray(1);

     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, position));
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, uv));

     float vertices[] = {
          -1.0f, -1.0f, 0.0f, 0.0f,
          -1.0f, 1.0f, 0.0f, 1.0f,
          1.0f, 1.0f, 1.0f, 1.0f,
          1.0f, -1.0f, 1.0f, 0.0f
     };

     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     glGenBuffers(1, m_eboID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);

     unsigned int indices[] = {0, 1, 2, 0, 2, 3};

     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     glBindVertexArray(0);

}

void Quad::render(){
     glBindVertexArray(m_vaoID);
     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
     glBindVertexArray(0);
}

void Quad::destroy(){

}
