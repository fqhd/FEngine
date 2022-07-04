#include "CubemapTexture.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Image.hpp"

void CubemapTexture::loadFromDirectory(const std::string& path) {

     std::vector<std::string> faces;

     faces.push_back(path + "bottom.png");
     faces.push_back(path + "front.png");
     faces.push_back(path + "top.png");
     faces.push_back(path + "back.png");
     faces.push_back(path + "right.png");
     faces.push_back(path + "left.png");


     glGenTextures(1, &m_textureID);
     glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

     for (unsigned int i = 0; i < faces.size(); i++) {
          Image image;
          image.loadFromFile(faces[i].c_str());
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
          image.free();
     }


     glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

GLuint CubemapTexture::getID(){
     return m_textureID;
}

void CubemapTexture::destroy(){
     glDeleteTextures(1, &m_textureID);
}
