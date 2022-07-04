#pragma once

#include <string>
#include <GL/glew.h>
#include "GLTexture.hpp"

class Texture
{
public:
    void init(const std::string &aPath, const std::string &nPath, const std::string &sPath);
    void bind();
    void unbind();
    void destroy();

    GLuint getID();

private:
    GLTexture albedo;
    GLTexture normal;
    GLTexture specular;
};