#pragma once

#include <string>
#include <GLAD/glad.h>
#include <FEngine/GLTexture.hpp>

class Texture
{
public:
    void init(const std::string &aPath, Color color);
    void bind() const;
    void unbind();
    void destroy();

    GLuint getID();

private:
    GLTexture albedo;
};