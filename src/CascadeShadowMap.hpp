#pragma once

#include <GL/glew.h>

class CascadeShadowMap {
public:
    void init();

    GLuint fbo;
    GLuint shadowMap[3];
};