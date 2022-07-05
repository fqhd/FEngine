#pragma once

#include <string>
#include <GL/glew.h>
#include "Image.hpp"

class GLTexture
{
public:
    void init(const char* path, GLuint defaultTexture);
    void bind(GLenum loc) const;
    void unbind(GLenum loc) const;
    void destroy();

    GLuint id = 0;
};