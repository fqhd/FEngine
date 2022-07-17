#pragma once

#include <string>
#include <glad.h>
#include "GLTexture.hpp"

class Texture
{
public:
    void init(const std::string &aPath, const std::string &nPath, const std::string &sPath, Color color);
    void bind() const;
    void unbind();
    void destroy();

    GLuint getID();

private:
    GLTexture albedo;
    GLTexture normal;
    GLTexture specular;
};