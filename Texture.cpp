#include "Texture.hpp"
#include "stb_image.h"

void Texture::loadFromFile(const std::string& path){

     int width, height, numChannels;

     unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 4);

     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
     glGenerateMipmap(GL_TEXTURE_2D);

     glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID(){
     return m_textureID;
}

void Texture::destroy(){
     glDeleteTextures(1, &m_textureID);
}
