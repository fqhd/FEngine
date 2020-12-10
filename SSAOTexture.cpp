#include "SSAOTexture.hpp"

void SSAOTexture::init(unsigned int width, unsigned int height, std::vector<glm::vec3>& noise){

     glGenTextures(1, &m_textureID);

     glBindTexture(GL_TEXTURE_2D, m_textureID);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 4, 4, 0, GL_RGB, GL_FLOAT, &noise[0]);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

     glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint SSAOTexture::getID(){
     return m_textureID;
}

void SSAOTexture::destroy(){
     glDeleteTextures(1, &m_textureID);
}
