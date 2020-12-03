#pragma once

class GUIAssets {
public:

     void init();

     GLuint getBlankTextureID();

private:

     GLuint loadTexture(const char* path);

     GLuint m_blankTextureID;

};
