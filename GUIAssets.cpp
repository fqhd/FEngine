#include "GUIAssets.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void GUIAssets::init(){
     m_blankTextureID = loadTexture("res/textures/blank.png");
}

GLuint GUIAssets::getBlankTextureID(){
     return m_blankTextureID;
}

GLuint GUIAssets::loadTexture(const char* path){

     int x, y, n;
     unsigned char* data = stbi_load(path, &x, &y, &n, 4);

     if(!data){
          printf("Failed to load image %s\n", path);
     }

     GLuint tID;

     glGenTextures(1, &tID);
     glBindTexture(GL_TEXTURE_2D, tID);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

     glBindTexture(GL_TEXTURE_2D, 0);

     stbi_image_free(data);

     return tID;
}
