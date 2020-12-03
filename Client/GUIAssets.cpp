#include "GUIAssets.hpp"

void GUIAssets::init(){
     m_blankTextureID = loadTexture("res/textures/blank.png");
}

GLuint GUIAssets::getBlankTextureID(){
     return m_blankTextureID;
}

GLuint GUIAssets::loadTexture(const char* path){
     sf::Image image;
     image.loadFromFile(path);

     GLuint tID;

     glGenTextures(1, &tID);
     glBindTexture(GL_TEXTURE_2D, tID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

     glBindTexture(GL_TEXTURE_2D, 0);

     return tID;
}
