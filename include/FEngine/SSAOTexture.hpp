#pragma once

#include <glad.h>

class SSAOTexture {
public:
    void init();
    void destroy();

    GLuint textureID;
};