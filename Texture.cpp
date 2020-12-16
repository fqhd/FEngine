#include "Texture.hpp"

#include "stb_image.h"


void Texture::init(const std::string& path){

     int width = 0;
     int height = 0;
     int numChannels = 0;

     //Loading in data
     unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 4);

     //Generating texture
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glGenerateMipmap(GL_TEXTURE_2D);

     glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

     glBindTexture(GL_TEXTURE_2D, 0);

     stbi_image_free(data);

}

GLuint Texture::getID(){
     return m_textureID;
}
