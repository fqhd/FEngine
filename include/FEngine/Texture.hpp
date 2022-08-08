#pragma once

#include <string>
#include <GLAD/glad.h>
#include <FEngine/GLTexture.hpp>

class Texture
{
public:
    void init(const std::string &aPath, const std::string& aoPath, Color color);
    void bind() const;
    void unbind();
    void destroy();

private:
    GLTexture albedo;
    GLTexture ambient;
};