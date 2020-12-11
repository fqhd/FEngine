#ifndef GUIASSETS_H
#define GUIASSETS_H
#include <GL/glew.h>

class GUIAssets {
public:

     void init();

     GLuint getSpriteSheet();

private:

     GLuint loadTexture(const char* path);

     GLuint m_spriteSheet;

};

#endif
