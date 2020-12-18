#include "Texture.hpp"

#include "stb_image.h"


void Texture::init(const std::string& path){

     int width = 0;
     int height = 0;
     int numChannels = 0;

     //Loading in data
     unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &numChannels, 4);

     //Generating texture
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
     glGenerateMipmap(GL_TEXTURE_2D);

     glBindTexture(GL_TEXTURE_2D, 0);

     stbi_image_free(imageData);

}

void Texture::bind(){
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind(){
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID(){
     return m_textureID;
}

void Texture::destroy() {
     glDeleteTextures(1, &m_textureID);
}
