#pragma once

#include <string>
#include <GLAD/glad.h>
#include <FEngine/Image.hpp>
#include <FEngine/Color.hpp>

class GLTexture
{
public:
    void init(const char* path, Color color);
    void bind(GLenum loc) const;
    void unbind(GLenum loc);
    void destroy();

    GLuint id = 0;
};