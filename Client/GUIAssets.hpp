#pragma once
#include <GL/glew.h>

class GUIAssets {
public:

     void init();

     GLuint getBlankTextureID();

private:

     GLuint loadTexture(const char* path);

     GLuint m_blankTextureID;

};
