#include "IndexBuffer.hpp"
#include "Utils.hpp"


void IndexBuffer::init(){
     glGenBuffers(1, &m_eboID);
}

void IndexBuffer::uploadIndices(unsigned int* indicesData, unsigned int numIndices, GLenum usage){
     if(!indicesData){
          Utils::log("IndexBuffer: invalid indices data");
          return;
     }
     if(numIndices == 0){
          Utils::log("IndexBuffer: invalid number of indices");
          return;
     }
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData[0]) * numIndices, indicesData, usage);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     m_numIndices = numIndices;

}

void IndexBuffer::bind(){
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
}

void IndexBuffer::unbind(){
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::destroy(){
     glDeleteBuffers(1, &m_eboID);
}

GLuint IndexBuffer::getNumIndices(){
     return m_numIndices;
}
