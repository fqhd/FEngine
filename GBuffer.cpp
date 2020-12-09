#include "GBuffer.hpp"

void GBuffer::init(unsigned int width, unsigned int height){


     glGenFramebuffers(1, &m_fboID);
     glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

     // - position color buffer
     glGenTextures(1, &m_positionTextureID);
     glBindTexture(GL_TEXTURE_2D, m_positionTextureID);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

     // - normal color buffer
     glGenTextures(1, &m_normalTextureID);
     glBindTexture(GL_TEXTURE_2D, m_normalTextureID);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normalTextureID, 0);

     // - color + specular color buffer
     glGenTextures(1, &m_albedoTextureID);
     glBindTexture(GL_TEXTURE_2D, m_albedoTextureID);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedoTextureID, 0);

     // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
     unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
     glDrawBuffers(3, attachments);



     if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
          Utils::log(DISK, "Failed to create framebuffer: " + name);
     }
     glBindFramebuffer(GL_FRAMEBUFFER, 0, );


}

void GBuffer::bind(){
     glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
}

void GBuffer::unbind(){
     glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::destroy(){
     glDeleteFramebuffers(1, &m_fboID);
}

void GBuffer::getPositionTextureID(){
     return m_positionTextureID;
}

void GBuffer::getAlbedoTextureID(){
     return m_albedoTextureID;
}

void GBuffer::getNormalTextureID(){
     return m_normalTextureID;
}
