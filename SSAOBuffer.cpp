#include "SSAOBuffer.hpp"


void SSAOBuffer::init(unsigned int width, unsigned int height){

     glGenFramebuffers(1, &m_fboID);
     glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_FLOAT, nullptr);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

     glBindTexture(GL_TEXTURE_2D, 0);

     glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void SSAOBuffer::clear(){
     glClear(GL_COLOR_BUFFER_BIT);
}

void SSAOBuffer::bind(){
     glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
}

void SSAOBuffer::unbind(){
     glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAOBuffer::destroy(){
     glDeleteTextures(1, &m_textureID);
     glDeleteFramebuffers(1, &m_fboID);
}


GLuint SSAOBuffer::getTextureID(){
     return m_textureID;
}
