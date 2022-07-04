#include "Texture.hpp"
#include "../Utils/Image.hpp"


void Texture::init(const std::string& path){

     //Loading in data
     Image image;
     image.loadFromFile(path.c_str());

     //Generating texture
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_2D, m_textureID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
     glGenerateMipmap(GL_TEXTURE_2D);

     glBindTexture(GL_TEXTURE_2D, 0);

     image.free();

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
