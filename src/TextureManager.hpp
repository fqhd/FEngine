#pragma once

#include "Texture.hpp"

class TextureManager
{
public:
    void init();
    Texture loadTexture(const std::string &aPath, const std::string &nPath, const std::string &sPath);
    void bindTexture(const Texture &texture) const;
    void unbindTexture(const Texture &texture) const;
    void destroyTexture(Texture& texture);

private:
    GLuint defaultAlbedo;
    GLuint defaultNormal;
    GLuint defaultSpecular;
};