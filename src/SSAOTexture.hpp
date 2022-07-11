#pragma once

#include <GL/glew.h>

class SSAOTexture {
public:
    void init();
    void destroy();

    GLuint textureID;
};