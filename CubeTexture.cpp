#include "CubeTexture.hpp"
#include "stb_image.h"
#include "Utils.hpp"

void CubeTexture::loadFromFile(const std::vector<std::string>& faces) {
     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

     int width, height, nrChannels;
     for (unsigned int i = 0; i < faces.size(); i++) {
          unsigned char* imageData = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
          if (!imageData){
               Utils::log("Failed to load in cubemap texture: " + faces[i]);
          }
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
          stbi_image_free(imageData);
     }


     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

GLuint CubeTexture::getID(){
     return m_textureID;

}

void CubeTexture::destroy(){
     glDeleteTextures(1, &m_textureID);
}
