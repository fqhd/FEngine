#pragma once

#include <GL/glew.h>

class CascadeShadowMap {
public:
    void init();
    void bindForReading();
    void bindForWriting(int index);

    GLuint fbo;
    GLuint shadowMap[3];
};