#pragma once

#include <GL/glew.h>
#include <string>

class GBuffer
{
public:
    void init(unsigned int width, unsigned int height);
    void bind();
    void unbind();
    void destroy();

    GLuint fboID = 0;
    GLuint rboID = 0;
    GLuint positionTextureID = 0;
    GLuint albedoTextureID = 0;
    GLuint normalTextureID = 0;
    GLuint depthTexture;
};